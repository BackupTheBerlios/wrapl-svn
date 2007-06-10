#include <Std.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <Riva/Memory.h>

#ifdef WINDOWS
#define PATHSEPCHR '\\'
#define PATHSEPSTR "\\"
#else
#define PATHSEPCHR '/'
#define PATHSEPSTR "/"
#endif

GLOBAL_FUNCTION(Path, 0) {
	
};

GLOBAL_FUNCTION(MakeDir, 2) {
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	if (mkdir(DirName, ((Std$Integer_smallt *)Args[0].Val)->Value)) {
		Result->Val = "Error creating directory";
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(RemoveDir, 1) {
	char DirName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, DirName);
	if (rmdir(DirName)) {
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
	if (unlink(FileName)) {
		Result->Val = "Error unlinking file";
		return MESSAGE;
	};
	return SUCCESS;
};

GLOBAL_FUNCTION(Rename, 2) {
	char OldName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, OldName);
	char NewName[((Std$String_t *)Args[1].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[1].Val, NewName);
	if (rename(OldName, NewName) == -1) {
		Result->Val = "Error renaming file";
		return MESSAGE;
	};
	return SUCCESS;
};

typedef struct listdir_generator {
	Std$Function_cstate State;
	DIR *Dir;
} listdir_generator;

typedef struct listdir_resume_data {
	listdir_generator *Generator;
	Std$Function_argument Result;
} listdir_resume_data;

static long listdir_resume(listdir_resume_data *Data) {
	listdir_generator *Generator = Data->Generator;
	struct dirent *Entry = readdir(Generator->Dir);
	if (Entry == 0) {
		closedir(Generator->Dir);
		return FAILURE;
	};
	int Length = strlen(Entry->d_name);
	char *FileName = Riva$Memory$alloc_atomic(Length + 1);
	strcpy(FileName, Entry->d_name);
	FileName[Length] = 0;
	Data->Result.Val = Std$String$new_length(FileName, Length);
	return SUSPEND;
};

GLOBAL_FUNCTION(ListDir, 1) {
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
	int Length = strlen(Entry->d_name);
	char *FileName = Riva$Memory$alloc_atomic(Length + 1);
	strcpy(FileName, Entry->d_name);
	FileName[Length] = 0;
	Result->Val = Std$String$new_length(FileName, Length);
	listdir_generator *Generator = new(listdir_generator);
	Generator->State.Run = Std$Function$resume_c;
	Generator->State.Invoke = listdir_resume;
	Generator->Dir = Dir;
	Result->State = Generator;
	return SUSPEND;
};

GLOBAL_FUNCTION(Exists, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		Result->Val = Args[0].Val;
		return SUCCESS;
	} else {
		return FAILURE;
	};
};

GLOBAL_FUNCTION(FileSize, 1) {
	char FileName[((Std$String_t *)Args[0].Val)->Length.Value + 1];
	Std$String$flatten_to(Args[0].Val, FileName);
	struct stat Stat;
	if (stat(FileName, &Stat) == 0) {
		Result->Val = Std$Integer$new_small(Stat.st_size);
		return SUCCESS;
	} else {
		return FAILURE;
	};
};
