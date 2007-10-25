#include <Std.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <Riva/Memory.h>

#ifdef WINDOWS
#include <windows.h>
#define PATHSEPCHR '\\'
#define PATHSEPSTR "\\"
#else
#define PATHSEPCHR '/'
#define PATHSEPSTR "/"
#endif

#ifdef WINDOWS
Std$Integer_smallt BLOCKFILE[] = {{Std$Integer$SmallT, 0}};
Std$Integer_smallt CHARFILE[] = {{Std$Integer$SmallT, 0}};
Std$Integer_smallt FIFOFILE[] = {{Std$Integer$SmallT, 0}};
Std$Integer_smallt REGFILE[] = {{Std$Integer$SmallT, 0}};
Std$Integer_smallt DIRFILE[] = {{Std$Integer$SmallT, 0}};
Std$Integer_smallt LINKFILE[] = {{Std$Integer$SmallT, 0}};
#else
Std$Integer_smallt BLOCKFILE[] = {{Std$Integer$SmallT, S_IFBLK}};
Std$Integer_smallt CHARFILE[] = {{Std$Integer$SmallT, S_IFCHR}};
Std$Integer_smallt FIFOFILE[] = {{Std$Integer$SmallT, S_IFIFO}};
Std$Integer_smallt REGFILE[] = {{Std$Integer$SmallT, S_IFREG}};
Std$Integer_smallt DIRFILE[] = {{Std$Integer$SmallT, S_IFDIR}};
Std$Integer_smallt LINKFILE[] = {{Std$Integer$SmallT, S_IFLNK}};
#endif

TYPE(InfoT);

typedef struct info_t {
	Std$Type_t *Type;
	Std$Object_t *Name;
	Std$Object_t *Kind;
	Std$Object_t *Size;
	Std$Object_t *Created;
	Std$Object_t *Modified;
	Std$Object_t *Accessed;
} info_t;

METHOD("name", TYP, InfoT) {
	Result->Val = ((info_t *)Args[0].Val)->Name;
	return SUCCESS;
};

METHOD("type", TYP, InfoT) {
	Result->Val = ((info_t *)Args[0].Val)->Kind;
	return SUCCESS;
};

METHOD("size", TYP, InfoT) {
	Result->Val = ((info_t *)Args[0].Val)->Size;
	return SUCCESS;
};

GLOBAL_FUNCTION(Path, 0) {
	
};

GLOBAL_FUNCTION(MakeDir, 2) {
#ifdef WINDOWS
	if (CreateDirectory(Std$String$flatten(Args[0].Val), 0) == 0) {
#else
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	if (mkdir(DirName, ((Std$Integer_smallt *)Args[1].Val)->Value)) {
#endif
		Result->Val = "Error creating directory";
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(RemoveDir, 1) {
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
#ifdef WINDOWS
	if (RemoveDirectory(DirName) == 0) {
#else
	if (rmdir(DirName)) {
#endif
		Result->Val = "Error removing directory";
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(Copy, 2) {
};

GLOBAL_FUNCTION(Remove, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
#ifdef WINDOWS
	if (DeleteFile(FileName) == 0) {
#else
	if (unlink(FileName)) {
#endif
		Result->Val = "Error unlinking file";
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(Rename, 2) {
	char OldName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	char NewName[((Std$String_t *)Args[1].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[1].Val, NewName);
	Std$String$flatten_to(Args[0].Val, OldName);
#ifdef WINDOWS
	if (MoveFile(OldName, NewName) == 0) {
#else
	if (rename(OldName, NewName) == -1) {
#endif
		Result->Val = "Error renaming file";
		return MESSAGE;
	};
	return SUCCESS;
};

typedef struct listdir_generator {
	Std$Function_cstate State;
#ifdef WINDOWS
#else
	DIR *Dir;
#endif
} listdir_generator;
typedef struct listdir_resume_data {
	listdir_generator *Generator;
	Std$Function_argument Result;
} listdir_resume_data;

static void listdir_finalize(listdir_generator *Gen, void *Arg) {
#ifdef LINUX
	closedir(Gen->Dir);
#endif
};

static long listdir_resume(listdir_resume_data *Data) {
#ifdef WINDOWS
#else
	listdir_generator *Generator = Data->Generator;
	struct dirent *Entry = readdir(Generator->Dir);
	if (Entry == 0) {
		closedir(Generator->Dir);
		Riva$Memory$register_finalizer(Generator, 0, 0, 0, 0);
		return FAILURE;
	};
	Data->Result.Val = Std$String$copy(Entry->d_name);
	return SUSPEND;
#endif
};

GLOBAL_FUNCTION(ListDir, 1) {
#ifdef WINDOWS
#else
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	DIR *Dir = opendir(DirName);
	if (Dir == 0) {
		Result->Val = "Error opening directory";
		return MESSAGE;
	};
	struct dirent *Entry = readdir(Dir);
	if (Entry == 0) {
		closedir(Dir);
		return FAILURE;
	};
	Result->Val = Std$String$copy(Entry->d_name);
	listdir_generator *Generator = new(listdir_generator);
	Riva$Memory$register_finalizer(Generator, listdir_finalize, 0, 0, 0);
	Riva$Memory$register_disappearing_link(&Generator->State.Chain);
	Generator->State.Run = Std$Function$resume_c;
	Generator->State.Invoke = listdir_resume;
	Generator->Dir = Dir;
	Result->State = Generator;
	return SUSPEND;
#endif
};

static long listdirinfo_resume(listdir_resume_data *Data) {
#ifdef WINDOWS
#else
	listdir_generator *Generator = Data->Generator;
	struct dirent *Entry = readdir(Generator->Dir);
	if (Entry == 0) {
		closedir(Generator->Dir);
		Riva$Memory$register_finalizer(Generator, 0, 0, 0, 0);
		return FAILURE;
	};
	info_t *Info = new(info_t);
	Info->Type = InfoT;
	Info->Name = Std$String$copy(Entry->d_name);
	switch (Entry->d_type) {
	case DT_REG:
		Info->Kind = REGFILE;
		break;
	case DT_DIR:
		Info->Kind = DIRFILE;
		break;
	case DT_FIFO:
		Info->Kind = FIFOFILE;
		break;
//	case DT_SOCK:
//		Info->Kind = SOCKFILE;
//		break;
	case DT_CHR:
		Info->Kind = CHARFILE;
		break;
	case DT_BLK:
		Info->Kind = BLOCKFILE;
		break;
	default:
		Info->Kind = Std$Object$Nil;
		break;
	};
	Info->Size = Std$Object$Nil;
	Data->Result.Val = Info;
	return SUSPEND;
#endif
};

GLOBAL_FUNCTION(ListDirInfo, 1) {
#ifdef WINDOWS
#else
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	DIR *Dir = opendir(DirName);
	if (Dir == 0) {
		Result->Val = "Error opening directory";
		return MESSAGE;
	};
	struct dirent *Entry = readdir(Dir);
	if (Entry == 0) {
		closedir(Dir);
		return FAILURE;
	};
	info_t *Info = new(info_t);
	Info->Type = InfoT;
	Info->Name = Std$String$copy(Entry->d_name);
	switch (Entry->d_type) {
	case DT_REG:
		Info->Kind = REGFILE;
		break;
	case DT_DIR:
		Info->Kind = DIRFILE;
		break;
	case DT_FIFO:
		Info->Kind = FIFOFILE;
		break;
//	case DT_SOCK:
//		Info->Kind = SOCKFILE;
//		break;
	case DT_CHR:
		Info->Kind = CHARFILE;
		break;
	case DT_BLK:
		Info->Kind = BLOCKFILE;
		break;
	default:
		Info->Kind = Std$Object$Nil;
		break;
	};
	Info->Size = Std$Object$Nil;
	Result->Val = Info;
	listdir_generator *Generator = new(listdir_generator);
	Riva$Memory$register_finalizer(Generator, listdir_finalize, 0, 0, 0);
	Riva$Memory$register_disappearing_link(&Generator->State.Chain);
	Generator->State.Run = Std$Function$resume_c;
	Generator->State.Invoke = listdirinfo_resume;
	Generator->Dir = Dir;
	Result->State = Generator;
	return SUSPEND;
#endif
};

GLOBAL_FUNCTION(Exists, 1) {
#ifdef WINDOWS
#else
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		Result->Val = Args[0].Val;
		return SUCCESS;
	} else {
		return FAILURE;
	};
#endif
};

GLOBAL_FUNCTION(FileSize, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
#ifdef WINDOWS
#else
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		Result->Val = Std$Integer$new_small(Stat.st_size);
		return SUCCESS;
	} else {
		return FAILURE;
	};
#endif
};

GLOBAL_FUNCTION(FileType, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
#ifdef WINDOWS
#else
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		Result->Val = Std$Integer$new_small(Stat.st_mode);
		return SUCCESS;
	} else {
		return FAILURE;
	};
#endif
};
GLOBAL_FUNCTION(FileInfo, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
#ifdef WINDOWS
#else
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		info_t *Info = new(info_t);
		Info->Type = InfoT;
		Info->Name = Args[0].Val;
		Info->Kind = Std$Integer$new_small(Stat.st_mode);
		Info->Size = Std$Integer$new_small(Stat.st_size);
		Result->Val = Info; 
		return SUCCESS;
	} else {
		return FAILURE;
	};
#endif
};

GLOBAL_FUNCTION(TempFile, 0) {
	Result->Val = Std$String$copy(tmpnam(0));
	return SUCCESS;
};
