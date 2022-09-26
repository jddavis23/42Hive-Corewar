# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caruychen <cchen@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 17:20:05 by caruychen         #+#    #+#              #
#    Updated: 2022/09/26 10:45:56 by cchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR := ./src
SRCS := $(SRC_DIR)/main.c
SRCS += $(SRC_DIR)/validator.c
SRCS += $(SRC_DIR)/source.c
SRCS += $(SRC_DIR)/source_read.c
SRCS += $(SRC_DIR)/lexer.c
SRCS += $(SRC_DIR)/opmap.c
SRCS += $(SRC_DIR)/cleanup.c
