/*
 * (C) Copyright 2008-2017 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ROCKCHIP_PANEL_H_
#define _ROCKCHIP_PANEL_H_


struct rockchip_cmd_header {
	u8 data_type;
	u8 delay_ms;
	u8 payload_length;
} __packed;

struct rockchip_cmd_desc {
	struct rockchip_cmd_header header;
	const u8 *payload;
};

struct rockchip_panel_cmds {
	struct rockchip_cmd_desc *cmds;
	int cmd_cnt;
};

struct rockchip_panel_id {
	u8 *buf;
	int len;
};

struct rockchip_panel_plat {
	bool power_invert;
	u32 bus_format;
	unsigned int bpc;
	unsigned int num;
	unsigned int id_reg;

	struct rockchip_panel_id *id;
	char *target_id;

	struct {
		unsigned int prepare;
		unsigned int unprepare;
		unsigned int enable;
		unsigned int disable;
		unsigned int reset;
		unsigned int init;
	} delay;

	struct rockchip_panel_cmds *on_cmds;
	struct rockchip_panel_cmds *off_cmds;
};

struct display_state;
struct rockchip_panel;

struct rockchip_panel_funcs {
	void (*init)(struct rockchip_panel *panel);
	void (*prepare)(struct rockchip_panel *panel);
	void (*unprepare)(struct rockchip_panel *panel);
	void (*enable)(struct rockchip_panel *panel);
	void (*disable)(struct rockchip_panel *panel);
	void (*getId)(struct rockchip_panel *panel);
};

struct rockchip_panel {
	struct udevice *dev;
	u32 bus_format;
	unsigned int bpc;
	const struct rockchip_panel_funcs *funcs;
	const void *data;

	struct display_state *state;
};

static inline void rockchip_panel_init(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->init)
		panel->funcs->init(panel);
}

static inline void rockchip_panel_prepare(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->prepare)
		panel->funcs->prepare(panel);
}

static inline void rockchip_panel_enable(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->enable)
		panel->funcs->enable(panel);
}

static inline void rockchip_panel_unprepare(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->unprepare)
		panel->funcs->unprepare(panel);
}

static inline void rockchip_panel_disable(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->disable)
		panel->funcs->disable(panel);
}

static inline void rockchip_panel_getId(struct rockchip_panel *panel)
{
	if (!panel)
		return;

	if (panel->funcs && panel->funcs->getId)
		panel->funcs->getId(panel);
}

#endif	/* _ROCKCHIP_PANEL_H_ */
