/**************************************************************************************
* Copyright (C) 2018-2019 uavs3d project
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the Open-Intelligence Open Source License V1.1.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* Open-Intelligence Open Source License V1.1 for more details.
*
* You should have received a copy of the Open-Intelligence Open Source License V1.1
* along with this program; if not, you can download it on:
* http://www.aitisa.org.cn/uploadfile/2018/0910/20180910031548314.pdf
*
* For more information, contact us at rgwang@pkusz.edu.cn.
**************************************************************************************/

#include "def_arm64.S"

#if defined(__arm64__)
//*************************************************************************************************
//void uavs3d_itrans_dct8_pb4_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it);
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************
function uavs3d_itrans_dct8_pb4_arm64

    neg w15, w2
    dup v31.4s, w15

    //load 变换系数
    mov x8, #0
    add x8, x8, x7
    mov x10, #4
    ld1	{v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
    //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0
    //load src
    lsl x3, x3, #1
    mov x8, #0

loopi:
    add x9, x8, x0
    ld1 {v4.4h}, [x9], x3
    ld1 {v5.4h}, [x9], x3
    ld1 {v6.4h}, [x9], x3
    ld1 {v7.4h}, [x9], x3

    //计算第一列
    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    cmp x2, #5
    bne dct8_pb4_shift12

    sqrshrn v16.4h, v16.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v16.4h, v16.4h, v18.4h
    smax v16.4h, v16.4h, v17.4h
    b dct8_pb4_store


dct8_pb4_shift12:
    srshl v16.4s, v16.4s, v31.4s
    sqxtn v16.4h, v16.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v16.4h, v16.4h, v18.4h
    smax v16.4h, v16.4h, v17.4h

dct8_pb4_store:
    st1 {v16.4h}, [x1]
    add x1, x1, #8

    add x8, x8, #2

    cmp x8, x3
    blo loopi
ret

//*************************************************************************************************
//void uavs3d_itrans_dct8_pb8_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it);
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************
function uavs3d_itrans_dct8_pb8_arm64
    neg w15, w2
    dup v31.4s, w15

    mov x13, #0 //i
dct8_pb8_loopi:
    mov x12, #0 //j
    mov x11, x7
dct8_pb8_loopj:
    mov w8, #0
    dup v20.4s,w8
    mov x9, #0
dct8_pb8_loopk:
    mov x14, x3
    mov x8, #0
    add x8, x8, x11
    mov x10, #8
    ld1 {v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
     //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0

    lsl x14, x14, #1
    mov x8, #0
    add x8, x8, x0
    ld1 {v4.4h}, [x8], x14
    ld1 {v5.4h}, [x8], x14
    ld1 {v6.4h}, [x8], x14
    ld1 {v7.4h}, [x8], x14

    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    add v20.4s, v16.4s, v20.4s
    add x11, x11, #32  //改变系数指针
    mov x8, x14
    lsl x8, x8, #2
    add x0, x0, x8 //改变源指针
    add x9, x9, #1 //k
    cmp x9, #2
    blo dct8_pb8_loopk

    cmp x2, #5
    bne dct8_pb8_shift12

    sqrshrn v20.4h, v20.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h
    b dct8_pb8_store

dct8_pb8_shift12:
	srshl v20.4s, v20.4s, v31.4s
    sqxtn v20.4h, v20.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h

dct8_pb8_store:
    st1 {v20.4h}, [x1]
    mov x8, x3
    lsl x8, x8, #4
    sub x0, x0, x8
    sub x11, x11, #60
    add x1, x1, #8
    add x12, x12, #1
    cmp x12, #2
    blo dct8_pb8_loopj

    add x0, x0, #2
    add x13, x13, #1
    cmp x13, x3
    blo dct8_pb8_loopi
ret

//*************************************************************************************************
//void uavs3d_itrans_dct8_pb16_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it)
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************
function uavs3d_itrans_dct8_pb16_arm64
    neg w15, w2
    dup v31.4s, w15

    mov x13, #0 //i
dct8_pb16_loopi:
    mov x12, #0 //j
    mov x11, x7
dct8_pb16_loopj:
    mov w8, #0
    dup v20.4s,w8
    mov x9, #0
dct8_pb16_loopk:
    mov x14, x3
    mov x8, #0
    add x8, x8, x11
    mov x10, #16
    ld1 {v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
     //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0

    lsl x14, x14, #1
    mov x8, #0
    add x8, x8, x0
    ld1 {v4.4h}, [x8], x14
    ld1 {v5.4h}, [x8], x14
    ld1 {v6.4h}, [x8], x14
    ld1 {v7.4h}, [x8], x14

    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    add v20.4s, v16.4s, v20.4s
    add x11, x11, #64  //改变系数指针
    mov x8, x14
    lsl x8, x8, #2
    add x0, x0, x8 //改变源指针
    add x9, x9, #1 //x9->k
    cmp x9, #4
    blo dct8_pb16_loopk

    cmp x2, #5
    bne dct8_pb16_shift12

    sqrshrn v20.4h, v20.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h
    b dct8_pb16_store

dct8_pb16_shift12:
	srshl v20.4s, v20.4s, v31.4s
    sqxtn v20.4h, v20.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h

dct8_pb16_store:
    st1 {v20.4h}, [x1]
    mov x8, x3
    lsl x8, x8, #5
    sub x0, x0, x8
    sub x11, x11, #252
    add x1, x1, #8
    add x12, x12, #1
    cmp x12, #4
    blo dct8_pb16_loopj

    add x0, x0, #2
    add x13, x13, #1
    cmp x13, x3
    blo dct8_pb16_loopi
ret


//*************************************************************************************************
//void uavs3d_itrans_dst7_pb4_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it);
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************

function uavs3d_itrans_dst7_pb4_arm64
    neg w15, w2
    dup v31.4s, w15
    //load 变换系数
    mov x8, #0
    add x8, x8, x7
    mov x10, #4
    ld1	{v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
    //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0
    //load src
    lsl x3, x3, #1
    mov x8, #0

dst7_pb4_loopi:
    add x9, x8, x0
    ld1 {v4.4h}, [x9], x3
    ld1 {v5.4h}, [x9], x3
    ld1 {v6.4h}, [x9], x3
    ld1 {v7.4h}, [x9], x3

    //计算第一列
    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    cmp x2, #5
    bne dst7_pb4_shift12

    sqrshrn v16.4h, v16.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v16.4h, v16.4h, v18.4h
    smax v16.4h, v16.4h, v17.4h
    b dst7_pb4_store


dst7_pb4_shift12:
	srshl v16.4s, v16.4s, v31.4s
    sqxtn v16.4h, v16.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v16.4h, v16.4h, v18.4h
    smax v16.4h, v16.4h, v17.4h

dst7_pb4_store:
    st1 {v16.4h}, [x1]
    add x1, x1, #8

    add x8, x8, #2

    cmp x8, x3
    blo dst7_pb4_loopi
ret

//*************************************************************************************************
//void uavs3d_itrans_dst7_pb8_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it);
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************
function uavs3d_itrans_dst7_pb8_arm64
    neg w15, w2
    dup v31.4s, w15
    mov x13, #0 //i
dst7_pb8_loopi:
    mov x12, #0 //j
    mov x11, x7
dst7_pb8_loopj:
    mov w8, #0
    dup v20.4s,w8
    mov x9, #0
dst7_pb8_loopk:
    mov x14, x3
    mov x8, #0
    add x8, x8, x11
    mov x10, #8
    ld1 {v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
     //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0

    lsl x14, x14, #1
    mov x8, #0
    add x8, x8, x0
    ld1 {v4.4h}, [x8], x14
    ld1 {v5.4h}, [x8], x14
    ld1 {v6.4h}, [x8], x14
    ld1 {v7.4h}, [x8], x14

    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    add v20.4s, v16.4s, v20.4s
    add x11, x11, #32  //改变系数指针
    mov x8, x14
    lsl x8, x8, #2
    add x0, x0, x8 //改变源指针
    add x9, x9, #1 //k
    cmp x9, #2
    blo dst7_pb8_loopk

    cmp x2, #5
    bne dst7_pb8_shift12

    sqrshrn v20.4h, v20.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h
    b dst7_pb8_store

dst7_pb8_shift12:
	srshl v20.4s, v20.4s, v31.4s
    sqxtn v20.4h, v20.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h

dst7_pb8_store:
    st1 {v20.4h}, [x1]
    mov x8, x3
    lsl x8, x8, #4
    sub x0, x0, x8
    sub x11, x11, #60
    add x1, x1, #8
    add x12, x12, #1
    cmp x12, #2
    blo dst7_pb8_loopj

    add x0, x0, #2
    add x13, x13, #1
    cmp x13, x3
    blo dst7_pb8_loopi
ret

//*************************************************************************************************
//void uavs3d_itrans_dst7_pb16_arm64(s16 *coeff, s16 *block, int shift, int line, int limit_line, int max_tr_val, int min_tr_val,s8 *it)
//x0->coeff blk, 16 bit
//x1->resi blk, 16 bit
//x7->transform block, 8bit
//*************************************************************************************************
function uavs3d_itrans_dst7_pb16_arm64
    neg w15, w2
    dup v31.4s, w15
    mov x13, #0 //i
dst7_pb16_loopi:
    mov x12, #0 //j
    mov x11, x7
dst7_pb16_loopj:
    mov w8, #0
    dup v20.4s,w8
    mov x9, #0
dst7_pb16_loopk:
    mov x14, x3
    mov x8, #0
    add x8, x8, x11
    mov x10, #16
    ld1 {v0.8b}, [x8], x10
    ld1 {v1.8b}, [x8], x10
    ld1 {v2.8b}, [x8], x10
    ld1 {v3.8b}, [x8], x10
     //扩展到16bit
    sshll v0.8h, v0.8b, #0
    sshll v1.8h, v1.8b, #0
    sshll v2.8h, v2.8b, #0
    sshll v3.8h, v3.8b, #0

    lsl x14, x14, #1
    mov x8, #0
    add x8, x8, x0
    ld1 {v4.4h}, [x8], x14
    ld1 {v5.4h}, [x8], x14
    ld1 {v6.4h}, [x8], x14
    ld1 {v7.4h}, [x8], x14

    smull v16.4s, v0.4h, v4.H[0]
    smull v17.4s, v1.4h, v5.H[0]
    smull v18.4s, v2.4h, v6.H[0]
    smull v19.4s, v3.4h, v7.H[0]
    sqadd v16.4s, v16.4s, v17.4s
    sqadd v18.4s, v18.4s, v19.4s
    sqadd v16.4s, v16.4s, v18.4s

    add v20.4s, v16.4s, v20.4s
    add x11, x11, #64  //改变系数指针
    mov x8, x14
    lsl x8, x8, #2
    add x0, x0, x8 //改变源指针
    add x9, x9, #1 //x9->k
    cmp x9, #4
    blo dst7_pb16_loopk

    cmp x2, #5
    bne dst7_pb16_shift12

    sqrshrn v20.4h, v20.4s, #5
    dup v17.4h, w6   //min_tr_val
    dup v18.4h, w5   //max_tr_val
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h
    b dst7_pb16_store

dst7_pb16_shift12:
	srshl v20.4s, v20.4s, v31.4s
    sqxtn v20.4h, v20.4s
    dup v17.4h,w6
    dup v18.4h,w5
    smin v20.4h, v20.4h, v18.4h
    smax v20.4h, v20.4h, v17.4h

dst7_pb16_store:
    st1 {v20.4h}, [x1]
    mov x8, x3
    lsl x8, x8, #5
    sub x0, x0, x8
    sub x11, x11, #252
    add x1, x1, #8
    add x12, x12, #1
    cmp x12, #4
    blo dst7_pb16_loopj

    add x0, x0, #2
    add x13, x13, #1
    cmp x13, x3
    blo dst7_pb16_loopi
ret


#endif
