#ifndef DISP_MANAGER_H
#define DISP_MANAGER_H

typedef struct disp_manager
{
    char *name;
    char (*dis_init)(void);
    char (*dis_deinit)(void);
    char (*dis_display)(void);
    struct disp_manager *next;

} DispOpr, *PDispOpr;

/* 注册一个显示驱动到链表头部 */
char dis_zc(PDispOpr int_g_DisDrv);
/* 按名字选中一个已注册的显示驱动 */
char dis_set(char *set_name);
/* 对当前选中的驱动做 init / display / deinit */
char dis_init(void);
char dis_display(void);
char dis_deinit(void);

#endif