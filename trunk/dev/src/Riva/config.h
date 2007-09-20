#ifndef CONFIG_H
#define CONFIG_H

extern const char *config_get(const char *);
extern void config_set(const char *, const char *);

extern void config_init(void);

#endif
