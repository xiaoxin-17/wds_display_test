#include "disp_manager.h"
#include <string.h>
#include <stddef.h>

/* 已注册的显示驱动链表头 */
static PDispOpr g_DisDrv = NULL;
/* 当前选中的显示驱动 */
static PDispOpr g_Dis = NULL;
pDIS_DATE gDIS_BUF;
/* 头插法：把 int_g_DisDrv 注册为新的链表头 */
char dis_zc(PDispOpr int_g_DisDrv)
{
	int_g_DisDrv->next = g_DisDrv;
	g_DisDrv = int_g_DisDrv;
	return 0;
}

/* 按名字找到对应驱动，并设为当前选中项 */
char dis_set(char *set_name)
{
	PDispOpr TEPM = g_DisDrv;
	while (TEPM)
	{
		if (strcmp(TEPM->name, set_name) == 0)
		{
			g_Dis = TEPM;
			return 0;
		}
		TEPM = TEPM->next;
	}
	return -1;
}

char dis_init(void)
{
	if (g_Dis)
		g_Dis->dis_init();
	if (g_Dis)
		g_Dis->dis_get_buf(&gDIS_BUF);

	return 0;
}

ptDIS_DATE GetDisplayBuffer(void)
{
	return &gDIS_BUF;
}

char dis_display(void)
{
	if (g_Dis)
		g_Dis->dis_display();
	return 0;
}

char FlushRegion(Pregion int_Pregion, ptDIS_DATE int_ptDIS_DATE)
{
	if (g_Dis)
		g_Dis->dis_FlushRegion( int_Pregion, int_ptDIS_DATE);
	return 0;
}

char dis_deinit(void)
{
	if (g_Dis)
		g_Dis->dis_deinit();
	return 0;
}