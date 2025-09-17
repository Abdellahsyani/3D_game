/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:15:56 by asyani            #+#    #+#             */
/*   Updated: 2025/09/15 10:17:01 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
#define DOOR_H

#include "cube.h"

typedef struct s_door
{
	int x_door;
	int y_door;
	double progress;
	int is_opening;
	int is_closing;
}	t_door;


#endif
