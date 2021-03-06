/*
 * Copyright (C) 2010 VMware, Inc.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _SNP_H
#define _SNP_H

/** @file
 *
 * SNP driver
 *
 */

FILE_LICENCE ( GPL2_OR_LATER );

#include <ipxe/device.h>
#include <ipxe/efi/efi.h>
#include <ipxe/efi/Protocol/SimpleNetwork.h>

/** An SNP device */
struct snp_device {
	/** EFI device */
	struct efi_device *efidev;
	/** Simple network protocol */
	EFI_SIMPLE_NETWORK_PROTOCOL *snp;
	/** Generic device */
	struct device dev;
	/** Network device */
	struct net_device *netdev;
	/** State to restore when removing the device */
	UINT32 removal_state;
};

#endif /* _SNP_H */
