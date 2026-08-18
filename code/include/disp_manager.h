#ifndef DISP_MANAGER_H
#define DISP_MANAGER_H

typedef struct DisDate
{
	int iXres;
	int iYres;
	int iBpp;
	unsigned char * Buf;
}pDIS_DATE,*ptDIS_DATE;

typedef struct Region{
	int iLeftUpX;
	int iLeftUpY;
	int iWidth;
	int iHeigh;
}Region, *Pregion;


typedef struct disp_manager
{
    char *name;
    char (*dis_init)(void);
    char (*dis_deinit)(void);
    char (*dis_get_buf)(ptDIS_DATE int_ptDIS_DATE);
    char (*dis_display)(void);
    char (*dis_FlushRegion)(Pregion int_Pregion, ptDIS_DATE int_ptDIS_DATE);
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

/* 获取显示缓冲区描述符（含分辨率/Bpp/显存地址） */
ptDIS_DATE GetDisplayBuffer(void);
/* 刷新指定区域到显存 */
char FlushRegion(Pregion int_Pregion, ptDIS_DATE int_ptDIS_DATE);

#endif