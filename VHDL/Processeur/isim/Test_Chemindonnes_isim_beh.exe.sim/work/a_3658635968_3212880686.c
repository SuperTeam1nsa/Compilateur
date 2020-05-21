/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x8ddf5b5d */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/hsahraou/Bureau/4A/COMPILATEUR/Compilateur/Compilateur/VHDL/ual.vhd";
extern char *IEEE_P_3620187407;
extern char *IEEE_P_2592010699;

char *ieee_p_3620187407_sub_1496620905533613331_3965413181(char *, char *, char *, char *, char *, char *);
char *ieee_p_3620187407_sub_1496620905533649268_3965413181(char *, char *, char *, char *, char *, char *);
char *ieee_p_3620187407_sub_1496620905533721142_3965413181(char *, char *, char *, char *, char *, char *);


static void work_a_3658635968_3212880686_p_0(char *t0)
{
    char t11[16];
    char t16[16];
    char t18[16];
    char t27[16];
    char t29[16];
    char *t1;
    char *t2;
    char *t3;
    int t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    int t10;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t17;
    char *t19;
    char *t20;
    int t21;
    unsigned int t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t28;
    char *t30;
    char *t31;
    int t32;
    char *t33;
    char *t34;
    unsigned int t35;
    unsigned char t36;
    char *t37;
    char *t38;
    char *t39;
    char *t40;
    char *t41;

LAB0:    xsi_set_current_line(43, ng0);
    t1 = (t0 + 1352U);
    t2 = *((char **)t1);
    t1 = (t0 + 8243);
    t4 = xsi_mem_cmp(t1, t2, 3U);
    if (t4 == 1)
        goto LAB3;

LAB7:    t5 = (t0 + 8246);
    t7 = xsi_mem_cmp(t5, t2, 3U);
    if (t7 == 1)
        goto LAB4;

LAB8:    t8 = (t0 + 8249);
    t10 = xsi_mem_cmp(t8, t2, 3U);
    if (t10 == 1)
        goto LAB5;

LAB9:
LAB6:    xsi_set_current_line(53, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t1 = (t0 + 8120U);
    t3 = (t0 + 1192U);
    t5 = *((char **)t3);
    t3 = (t0 + 8136U);
    t6 = ieee_p_3620187407_sub_1496620905533613331_3965413181(IEEE_P_3620187407, t11, t2, t1, t5, t3);
    t8 = (t11 + 12U);
    t22 = *((unsigned int *)t8);
    t35 = (1U * t22);
    t36 = (16U != t35);
    if (t36 == 1)
        goto LAB17;

LAB18:    t9 = (t0 + 5184);
    t12 = (t9 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    memcpy(t15, t6, 16U);
    xsi_driver_first_trans_fast(t9);

LAB2:    t1 = (t0 + 5024);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(45, ng0);
    t12 = (t0 + 8252);
    t14 = (t0 + 1032U);
    t15 = *((char **)t14);
    t17 = ((IEEE_P_2592010699) + 4000);
    t19 = (t18 + 0U);
    t20 = (t19 + 0U);
    *((int *)t20) = 0;
    t20 = (t19 + 4U);
    *((int *)t20) = 7;
    t20 = (t19 + 8U);
    *((int *)t20) = 1;
    t21 = (7 - 0);
    t22 = (t21 * 1);
    t22 = (t22 + 1);
    t20 = (t19 + 12U);
    *((unsigned int *)t20) = t22;
    t20 = (t0 + 8120U);
    t14 = xsi_base_array_concat(t14, t16, t17, (char)97, t12, t18, (char)97, t15, t20, (char)101);
    t23 = (t0 + 8260);
    t25 = (t0 + 1192U);
    t26 = *((char **)t25);
    t28 = ((IEEE_P_2592010699) + 4000);
    t30 = (t29 + 0U);
    t31 = (t30 + 0U);
    *((int *)t31) = 0;
    t31 = (t30 + 4U);
    *((int *)t31) = 7;
    t31 = (t30 + 8U);
    *((int *)t31) = 1;
    t32 = (7 - 0);
    t22 = (t32 * 1);
    t22 = (t22 + 1);
    t31 = (t30 + 12U);
    *((unsigned int *)t31) = t22;
    t31 = (t0 + 8136U);
    t25 = xsi_base_array_concat(t25, t27, t28, (char)97, t23, t29, (char)97, t26, t31, (char)101);
    t33 = ieee_p_3620187407_sub_1496620905533649268_3965413181(IEEE_P_3620187407, t11, t14, t16, t25, t27);
    t34 = (t11 + 12U);
    t22 = *((unsigned int *)t34);
    t35 = (1U * t22);
    t36 = (16U != t35);
    if (t36 == 1)
        goto LAB11;

LAB12:    t37 = (t0 + 5184);
    t38 = (t37 + 56U);
    t39 = *((char **)t38);
    t40 = (t39 + 56U);
    t41 = *((char **)t40);
    memcpy(t41, t33, 16U);
    xsi_driver_first_trans_fast(t37);
    goto LAB2;

LAB4:    xsi_set_current_line(47, ng0);
    t1 = (t0 + 1032U);
    t2 = *((char **)t1);
    t1 = (t0 + 8120U);
    t3 = (t0 + 1192U);
    t5 = *((char **)t3);
    t3 = (t0 + 8136U);
    t6 = ieee_p_3620187407_sub_1496620905533613331_3965413181(IEEE_P_3620187407, t11, t2, t1, t5, t3);
    t8 = (t11 + 12U);
    t22 = *((unsigned int *)t8);
    t35 = (1U * t22);
    t36 = (16U != t35);
    if (t36 == 1)
        goto LAB13;

LAB14:    t9 = (t0 + 5184);
    t12 = (t9 + 56U);
    t13 = *((char **)t12);
    t14 = (t13 + 56U);
    t15 = *((char **)t14);
    memcpy(t15, t6, 16U);
    xsi_driver_first_trans_fast(t9);
    goto LAB2;

LAB5:    xsi_set_current_line(49, ng0);
    t1 = (t0 + 8268);
    t3 = (t0 + 1032U);
    t5 = *((char **)t3);
    t6 = ((IEEE_P_2592010699) + 4000);
    t8 = (t18 + 0U);
    t9 = (t8 + 0U);
    *((int *)t9) = 0;
    t9 = (t8 + 4U);
    *((int *)t9) = 7;
    t9 = (t8 + 8U);
    *((int *)t9) = 1;
    t4 = (7 - 0);
    t22 = (t4 * 1);
    t22 = (t22 + 1);
    t9 = (t8 + 12U);
    *((unsigned int *)t9) = t22;
    t9 = (t0 + 8120U);
    t3 = xsi_base_array_concat(t3, t16, t6, (char)97, t1, t18, (char)97, t5, t9, (char)101);
    t12 = (t0 + 8276);
    t14 = (t0 + 1192U);
    t15 = *((char **)t14);
    t17 = ((IEEE_P_2592010699) + 4000);
    t19 = (t29 + 0U);
    t20 = (t19 + 0U);
    *((int *)t20) = 0;
    t20 = (t19 + 4U);
    *((int *)t20) = 7;
    t20 = (t19 + 8U);
    *((int *)t20) = 1;
    t7 = (7 - 0);
    t22 = (t7 * 1);
    t22 = (t22 + 1);
    t20 = (t19 + 12U);
    *((unsigned int *)t20) = t22;
    t20 = (t0 + 8136U);
    t14 = xsi_base_array_concat(t14, t27, t17, (char)97, t12, t29, (char)97, t15, t20, (char)101);
    t23 = ieee_p_3620187407_sub_1496620905533721142_3965413181(IEEE_P_3620187407, t11, t3, t16, t14, t27);
    t24 = (t11 + 12U);
    t22 = *((unsigned int *)t24);
    t35 = (1U * t22);
    t36 = (16U != t35);
    if (t36 == 1)
        goto LAB15;

LAB16:    t25 = (t0 + 5184);
    t26 = (t25 + 56U);
    t28 = *((char **)t26);
    t30 = (t28 + 56U);
    t31 = *((char **)t30);
    memcpy(t31, t23, 16U);
    xsi_driver_first_trans_fast(t25);
    goto LAB2;

LAB10:;
LAB11:    xsi_size_not_matching(16U, t35, 0);
    goto LAB12;

LAB13:    xsi_size_not_matching(16U, t35, 0);
    goto LAB14;

LAB15:    xsi_size_not_matching(16U, t35, 0);
    goto LAB16;

LAB17:    xsi_size_not_matching(16U, t35, 0);
    goto LAB18;

}

static void work_a_3658635968_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(57, ng0);

LAB3:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = (15 - 7);
    t4 = (t3 * 1U);
    t5 = (0 + t4);
    t1 = (t2 + t5);
    t6 = (t0 + 5248);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 8U);
    xsi_driver_first_trans_fast_port(t6);

LAB2:    t11 = (t0 + 5040);
    *((int *)t11) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_3658635968_3212880686_p_2(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;

LAB0:    xsi_set_current_line(65, ng0);

LAB3:    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = (7 - 15);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t0 + 5312);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    *((unsigned char *)t12) = t7;
    xsi_driver_first_trans_fast_port(t8);

LAB2:    t13 = (t0 + 5056);
    *((int *)t13) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void work_a_3658635968_3212880686_p_3(char *t0)
{
    char t38[16];
    char t78[16];
    unsigned char t1;
    unsigned char t2;
    unsigned char t3;
    char *t4;
    char *t5;
    int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned char t10;
    char *t11;
    char *t12;
    int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned char t17;
    unsigned char t18;
    char *t19;
    char *t20;
    int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned char t25;
    char *t26;
    char *t27;
    int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    unsigned char t32;
    unsigned char t33;
    char *t34;
    char *t35;
    char *t36;
    char *t39;
    char *t40;
    int t41;
    unsigned int t42;
    unsigned char t43;
    unsigned char t44;
    unsigned char t45;
    char *t46;
    int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned char t50;
    char *t51;
    char *t52;
    int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned char t57;
    unsigned char t58;
    char *t59;
    char *t60;
    int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned char t65;
    char *t66;
    char *t67;
    int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned char t72;
    unsigned char t73;
    char *t74;
    char *t75;
    char *t76;
    char *t79;
    char *t80;
    int t81;
    unsigned int t82;
    unsigned char t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;
    char *t88;
    char *t89;
    char *t90;
    char *t91;
    char *t92;
    char *t93;

LAB0:    xsi_set_current_line(68, ng0);
    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t6 = (7 - 7);
    t7 = (t6 * -1);
    t8 = (1U * t7);
    t9 = (0 + t8);
    t4 = (t5 + t9);
    t10 = *((unsigned char *)t4);
    t11 = (t0 + 1192U);
    t12 = *((char **)t11);
    t13 = (7 - 7);
    t14 = (t13 * -1);
    t15 = (1U * t14);
    t16 = (0 + t15);
    t11 = (t12 + t16);
    t17 = *((unsigned char *)t11);
    t18 = (t10 == t17);
    if (t18 == 1)
        goto LAB11;

LAB12:    t3 = (unsigned char)0;

LAB13:    if (t3 == 1)
        goto LAB8;

LAB9:    t2 = (unsigned char)0;

LAB10:    if (t2 == 1)
        goto LAB5;

LAB6:    t40 = (t0 + 1032U);
    t46 = *((char **)t40);
    t47 = (7 - 7);
    t42 = (t47 * -1);
    t48 = (1U * t42);
    t49 = (0 + t48);
    t40 = (t46 + t49);
    t50 = *((unsigned char *)t40);
    t51 = (t0 + 1192U);
    t52 = *((char **)t51);
    t53 = (7 - 7);
    t54 = (t53 * -1);
    t55 = (1U * t54);
    t56 = (0 + t55);
    t51 = (t52 + t56);
    t57 = *((unsigned char *)t51);
    t58 = (t50 != t57);
    if (t58 == 1)
        goto LAB17;

LAB18:    t45 = (unsigned char)0;

LAB19:    if (t45 == 1)
        goto LAB14;

LAB15:    t44 = (unsigned char)0;

LAB16:    t1 = t44;

LAB7:    if (t1 != 0)
        goto LAB3;

LAB4:
LAB20:    t88 = (t0 + 5376);
    t89 = (t88 + 56U);
    t90 = *((char **)t89);
    t91 = (t90 + 56U);
    t92 = *((char **)t91);
    *((unsigned char *)t92) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t88);

LAB2:    t93 = (t0 + 5072);
    *((int *)t93) = 1;

LAB1:    return;
LAB3:    t80 = (t0 + 5376);
    t84 = (t80 + 56U);
    t85 = *((char **)t84);
    t86 = (t85 + 56U);
    t87 = *((char **)t86);
    *((unsigned char *)t87) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t80);
    goto LAB2;

LAB5:    t1 = (unsigned char)1;
    goto LAB7;

LAB8:    t34 = (t0 + 1352U);
    t35 = *((char **)t34);
    t34 = (t0 + 8152U);
    t36 = (t0 + 8284);
    t39 = (t38 + 0U);
    t40 = (t39 + 0U);
    *((int *)t40) = 0;
    t40 = (t39 + 4U);
    *((int *)t40) = 2;
    t40 = (t39 + 8U);
    *((int *)t40) = 1;
    t41 = (2 - 0);
    t42 = (t41 * 1);
    t42 = (t42 + 1);
    t40 = (t39 + 12U);
    *((unsigned int *)t40) = t42;
    t43 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t35, t34, t36, t38);
    t2 = t43;
    goto LAB10;

LAB11:    t19 = (t0 + 2312U);
    t20 = *((char **)t19);
    t21 = (7 - 15);
    t22 = (t21 * -1);
    t23 = (1U * t22);
    t24 = (0 + t23);
    t19 = (t20 + t24);
    t25 = *((unsigned char *)t19);
    t26 = (t0 + 1032U);
    t27 = *((char **)t26);
    t28 = (7 - 7);
    t29 = (t28 * -1);
    t30 = (1U * t29);
    t31 = (0 + t30);
    t26 = (t27 + t31);
    t32 = *((unsigned char *)t26);
    t33 = (t25 != t32);
    t3 = t33;
    goto LAB13;

LAB14:    t74 = (t0 + 1352U);
    t75 = *((char **)t74);
    t74 = (t0 + 8152U);
    t76 = (t0 + 8287);
    t79 = (t78 + 0U);
    t80 = (t79 + 0U);
    *((int *)t80) = 0;
    t80 = (t79 + 4U);
    *((int *)t80) = 2;
    t80 = (t79 + 8U);
    *((int *)t80) = 1;
    t81 = (2 - 0);
    t82 = (t81 * 1);
    t82 = (t82 + 1);
    t80 = (t79 + 12U);
    *((unsigned int *)t80) = t82;
    t83 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t75, t74, t76, t78);
    t44 = t83;
    goto LAB16;

LAB17:    t59 = (t0 + 2312U);
    t60 = *((char **)t59);
    t61 = (7 - 15);
    t62 = (t61 * -1);
    t63 = (1U * t62);
    t64 = (0 + t63);
    t59 = (t60 + t64);
    t65 = *((unsigned char *)t59);
    t66 = (t0 + 1192U);
    t67 = *((char **)t66);
    t68 = (7 - 7);
    t69 = (t68 * -1);
    t70 = (1U * t69);
    t71 = (0 + t70);
    t66 = (t67 + t71);
    t72 = *((unsigned char *)t66);
    t73 = (t65 == t72);
    t45 = t73;
    goto LAB19;

LAB21:    goto LAB2;

}

static void work_a_3658635968_3212880686_p_4(char *t0)
{
    char t6[16];
    char t12[16];
    char *t1;
    char *t2;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    char *t7;
    char *t8;
    int t9;
    unsigned int t10;
    char *t13;
    char *t14;
    int t15;
    unsigned char t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;

LAB0:    xsi_set_current_line(71, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = (15 - 7);
    t4 = (t3 * 1U);
    t5 = (0 + t4);
    t1 = (t2 + t5);
    t7 = (t6 + 0U);
    t8 = (t7 + 0U);
    *((int *)t8) = 7;
    t8 = (t7 + 4U);
    *((int *)t8) = 0;
    t8 = (t7 + 8U);
    *((int *)t8) = -1;
    t9 = (0 - 7);
    t10 = (t9 * -1);
    t10 = (t10 + 1);
    t8 = (t7 + 12U);
    *((unsigned int *)t8) = t10;
    t8 = (t0 + 8290);
    t13 = (t12 + 0U);
    t14 = (t13 + 0U);
    *((int *)t14) = 0;
    t14 = (t13 + 4U);
    *((int *)t14) = 7;
    t14 = (t13 + 8U);
    *((int *)t14) = 1;
    t15 = (7 - 0);
    t10 = (t15 * 1);
    t10 = (t10 + 1);
    t14 = (t13 + 12U);
    *((unsigned int *)t14) = t10;
    t16 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t1, t6, t8, t12);
    if (t16 != 0)
        goto LAB3;

LAB4:
LAB5:    t21 = (t0 + 5440);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    t24 = (t23 + 56U);
    t25 = *((char **)t24);
    *((unsigned char *)t25) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t21);

LAB2:    t26 = (t0 + 5088);
    *((int *)t26) = 1;

LAB1:    return;
LAB3:    t14 = (t0 + 5440);
    t17 = (t14 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    *((unsigned char *)t20) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t14);
    goto LAB2;

LAB6:    goto LAB2;

}

static void work_a_3658635968_3212880686_p_5(char *t0)
{
    char *t1;
    char *t2;
    int t3;
    unsigned int t4;
    unsigned int t5;
    unsigned int t6;
    unsigned char t7;
    unsigned char t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;

LAB0:    xsi_set_current_line(72, ng0);
    t1 = (t0 + 2312U);
    t2 = *((char **)t1);
    t3 = (8 - 15);
    t4 = (t3 * -1);
    t5 = (1U * t4);
    t6 = (0 + t5);
    t1 = (t2 + t6);
    t7 = *((unsigned char *)t1);
    t8 = (t7 == (unsigned char)3);
    if (t8 != 0)
        goto LAB3;

LAB4:
LAB5:    t14 = (t0 + 5504);
    t15 = (t14 + 56U);
    t16 = *((char **)t15);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    *((unsigned char *)t18) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t14);

LAB2:    t19 = (t0 + 5104);
    *((int *)t19) = 1;

LAB1:    return;
LAB3:    t9 = (t0 + 5504);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    *((unsigned char *)t13) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t9);
    goto LAB2;

LAB6:    goto LAB2;

}


extern void work_a_3658635968_3212880686_init()
{
	static char *pe[] = {(void *)work_a_3658635968_3212880686_p_0,(void *)work_a_3658635968_3212880686_p_1,(void *)work_a_3658635968_3212880686_p_2,(void *)work_a_3658635968_3212880686_p_3,(void *)work_a_3658635968_3212880686_p_4,(void *)work_a_3658635968_3212880686_p_5};
	xsi_register_didat("work_a_3658635968_3212880686", "isim/Test_Chemindonnes_isim_beh.exe.sim/work/a_3658635968_3212880686.didat");
	xsi_register_executes(pe);
}
