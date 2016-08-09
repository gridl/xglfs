/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab */

/*
 * xglfs - GlusterFS API FUSE client
 * Copyright (C) Oleksandr Natalenko <oleksandr@natalenko.name>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"
#include "xglfs_utimens.h"

int xglfs_utimens(const char* _path, const struct timespec _tv[2])
{
	int ret = 0;

	/*
	 * Copy is needed to remove const qualifier.
	 * Probably, this is a bug in GFAPI.
	 * glfs_lutimes() should declare 3rd argument as const.
	 */
	struct timespec tv[2];
	tv[0] = _tv[0];
	tv[1] = _tv[1];

	ret = glfs_lutimens(XGLFS_STATE->fs, _path, tv);
	if (unlikely(ret < 0))
		ret = -errno;

	return ret;
}

