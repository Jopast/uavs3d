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

#if defined(__arm__)

#include "def_armv7.S"

// void uavs3d_avg_pel_w4_armv7(pel *dst, int i_dst, pel *src1, pel *src2, int width, int height);
function uavs3d_avg_pel_w4_armv7
// dst-->r0, i_dst-->r1, src1-->r2, src2-->r3, width-->r4, height-->r5

	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
	add sp, sp, #32
	ldmia sp, {r4, r5}
	sub sp, sp, #32

avg_pel_w4_y:
    vld1.8 {q0}, [r2]!
    vld1.8 {q1}, [r3]!
    vrhadd.u8 q2, q0, q1
    vmov r6, r7, d4
    vmov r8, r9, d5

    add  r10, r0, r1
    str  r6, [r0]
    add  r0, r1, lsl #1
    str  r7, [r10]          // dst + i_dst
    add  r10, r1, lsl #1
    str  r8, [r0]           // dst + i_dst*2
    str  r9, [r10]

    sub r5, r5, #4
    add r0, r1, lsl #1      // dst + i_dst*4
    cmp r5, #0

    bgt avg_pel_w4_y

	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, lr}
	mov pc, lr

//void uavs3d_avg_pel_w8_armv7(pel_t *dst, int i_dst, pel_t *src1, pel_t *src2, int width, int height);
// dst->r0, i_dst->r1, src1->r2, src2->r3, width->r4, height->r5
function uavs3d_avg_pel_w8_armv7
    stmdb sp!, {r4, r5, lr}
	add sp, sp, #12
	ldmia sp, {r4, r5}
	sub sp, sp, #12

avg_pel_w8_y:
    vld1.64 {q0, q1}, [r2]!
    vld1.64 {q2, q3}, [r3]!
    vrhadd.u8 q0, q0, q2
    vrhadd.u8 q1, q1, q3

    vst1.64 {d0}, [r0], r1
    vst1.64 {d1}, [r0], r1
    vst1.64 {d2}, [r0], r1
    vst1.64 {d3}, [r0], r1

    sub r5, r5, #4
    cmp r5, #0

    bgt avg_pel_w8_y

    ldmia sp!, {r4, r5, lr}
    mov pc, lr

//void uavs3d_avg_pel_w16_armv7(pel_t *dst, int i_dst, pel_t *src1, pel_t *src2, int width, int height);
//dst->r0, i_dst->r1, src1->r2, src2->r3, width->r4, height->r5
function uavs3d_avg_pel_w16_armv7
    push {r4, r5, lr}
	add sp, sp, #12
	ldmia sp, {r4, r5}
	sub sp, sp, #12

avg_pel_w16_y:
    vld1.64 {q0, q1}, [r2]!
    vld1.64 {q2, q3}, [r2]!
    vld1.64 {q10, q11}, [r3]!
    vld1.64 {q12, q13}, [r3]!
    vrhadd.u8 q0, q0, q10
    vrhadd.u8 q1, q1, q11
    vrhadd.u8 q2, q2, q12
    vrhadd.u8 q3, q3, q13

    sub r5, r5, #4
    vst1.64 {q0}, [r0], r1
    vst1.64 {q1}, [r0], r1
    vst1.64 {q2}, [r0], r1
    vst1.64 {q3}, [r0], r1

    cmp r5, #0
    bgt avg_pel_w16_y

    pop {r4, r5, lr}
    mov pc, lr

//void uavs3d_avg_pel_w32_armv7(pel_t *dst, int i_dst, pel_t *src1, pel_t *src2, int width, int height);
//dst->r0, i_dst->r1, src1->r2, src2->r3, width->r4, height->r5
function uavs3d_avg_pel_w32_armv7
    push {r4, r5, lr}
	add sp, sp, #12
	ldmia sp, {r4, r5}
	sub sp, sp, #12
    vpush {q4-q7}

avg_pel_w32_y:
    vld1.64 {q0, q1}, [r2]!
    vld1.64 {q2, q3}, [r2]!
    vld1.64 {q4, q5}, [r2]!
    vld1.64 {q6, q7}, [r2]!

    vld1.64 {q8, q9}, [r3]!
    vld1.64 {q10, q11}, [r3]!
    vld1.64 {q12, q13}, [r3]!
    vld1.64 {q14, q15}, [r3]!

    vrhadd.u8 q0, q0, q8
    vrhadd.u8 q1, q1, q9
    vrhadd.u8 q2, q2, q10
    vrhadd.u8 q3, q3, q11
    vrhadd.u8 q4, q4, q12
    vrhadd.u8 q5, q5, q13
    vrhadd.u8 q6, q6, q14
    vrhadd.u8 q7, q7, q15

    sub r5, r5, #4
    vst1.64  {q0, q1}, [r0], r1
    vst1.64  {q2, q3}, [r0], r1
    vst1.64  {q4, q5}, [r0], r1
    vst1.64  {q6, q7}, [r0], r1

    cmp r5, #0
    bgt avg_pel_w32_y

    vpop {q4-q7}
    pop {r4, r5, lr}
    mov pc, lr

//void uavs3d_avg_pel_w64_armv7(pel_t *dst, int i_dst, pel_t *src1, pel_t *src2, int width, int height);
//dst->r0, i_dst->r1, src1->r2, src2->r3, width->r4, height->r5
function uavs3d_avg_pel_w64_armv7
    push {r4, r5, lr}
	add sp, sp, #12
	ldmia sp, {r4, r5}
	sub sp, sp, #12
    vpush {q4-q7}
    sub r1, #32
avg_pel_w64_y:
    vld1.64 {q0, q1}, [r2]!
    vld1.64 {q2, q3}, [r2]!
    vld1.64 {q4, q5}, [r2]!
    vld1.64 {q6, q7}, [r2]!

    vld1.64 {q8, q9}, [r3]!
    vld1.64 {q10, q11}, [r3]!
    vld1.64 {q12, q13}, [r3]!
    vld1.64 {q14, q15}, [r3]!

    vrhadd.u8 q0, q0, q8
    vrhadd.u8 q1, q1, q9
    vrhadd.u8 q2, q2, q10
    vrhadd.u8 q3, q3, q11
    vrhadd.u8 q4, q4, q12
    vrhadd.u8 q5, q5, q13
    vrhadd.u8 q6, q6, q14
    vrhadd.u8 q7, q7, q15

    sub r5, r5, #2
    vst1.64 {q0, q1}, [r0]!
    vst1.64 {q2, q3}, [r0], r1
    vst1.64 {q4, q5}, [r0]!
    vst1.64 {q6, q7}, [r0], r1

    cmp r5, #0
    bgt avg_pel_w64_y

    vpop {q4-q7}
    pop {r4, r5, lr}
    mov pc, lr

//void uavs3d_avg_pel_w128_armv7(pel_t *dst, int i_dst, pel_t *src1, pel_t *src2, int width, int height);
//dst->r0, i_dst->r1, src1->r2, src2->r3, width->r4, height->r5
function uavs3d_avg_pel_w128_armv7
    push {r4, r5, lr}
	add sp, sp, #12
	ldmia sp, {r4, r5}
	sub sp, sp, #12
    vpush {q4-q7}
    sub r1, #96
avg_pel_w128_y:
    vld1.64 {q0, q1}, [r2]!
    vld1.64 {q2, q3}, [r2]!
    vld1.64 {q4, q5}, [r2]!
    vld1.64 {q6, q7}, [r2]!

    vld1.64 {q8, q9}, [r3]!
    vld1.64 {q10, q11}, [r3]!
    vld1.64 {q12, q13}, [r3]!
    vld1.64 {q14, q15}, [r3]!

    vrhadd.u8 q0, q0, q8
    vrhadd.u8 q1, q1, q9
    vrhadd.u8 q2, q2, q10
    vrhadd.u8 q3, q3, q11
    vrhadd.u8 q4, q4, q12
    vrhadd.u8 q5, q5, q13
    vrhadd.u8 q6, q6, q14
    vrhadd.u8 q7, q7, q15

    sub r5, r5, #1
    vst1.64 {q0, q1}, [r0]!
    vst1.64 {q2, q3}, [r0]!
    vst1.64 {q4, q5}, [r0]!
    vst1.64 {q6, q7}, [r0], r1

    cmp r5, #0
    bgt avg_pel_w128_y

    vpop {q4-q7}
    pop {r4, r5, lr}
    mov pc, lr

function uavs3d_avg_pel_rect_armv7
@*dst-->r0, i_dst-->r1, *src1-->r2, i_src1-->r3, *src2-->r4, i_src2-->r5, width-->r6, height-->r7
	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	add sp, sp, #40
	ldmia sp, {r4, r5, r6, r7}
	sub sp, sp, #40

	and r8,r6,#15
	cmp r8,#0
	beq avg_pel_rect16

	and r8,r6,#7
	cmp r8,#0
	beq avg_pel_rect8

	and r8,r6,#3
	cmp r8,#0
	beq avg_pel_rect4

avg_pel_rect2:

avg_pel_rect2_y:
	mov r8,r0
	mov r9,r2
	mov r10,r4
	mov r12,#0

avg_pel_rect2_x:
	vld1.16 {d0[0]},[r9]!
	vld1.16 {d1[0]},[r10]!
	vrhadd.u8 d2,d1,d0
	vst1.16 {d2[0]},[r8]!
	add r12,#2
	cmp r12,r6
	bne avg_pel_rect2_x

	add r0,r0,r1
	add r2,r2,r3
	add r4,r4,r5
	sub r7,r7,#1
	cmp r7,#0
	bne avg_pel_rect2_y

	b end_avg_pel_rect


avg_pel_rect4:

avg_pel_rect4_y:
	mov r8,r0
	mov r9,r2
	mov r10,r4
	mov r12,#0

avg_pel_rect4_x:
	vld1.32 {d0[0]},[r9]!
	vld1.32 {d1[0]},[r10]!
	vrhadd.u8 d2,d1,d0
	vst1.32 {d2[0]},[r8]!
	add r12,#4
	cmp r12,r6
	bne avg_pel_rect4_x

	add r0,r0,r1
	add r2,r2,r3
	add r4,r4,r5
	sub r7,r7,#1
	cmp r7,#0
	bne avg_pel_rect4_y

	b end_avg_pel_rect

avg_pel_rect8:

avg_pel_rect8_y:
	mov r8,r0
	mov r9,r2
	mov r10,r4
	mov r12,#0

avg_pel_rect8_x:
	vld1.8 {d0},[r9]!
	vld1.8 {d1},[r10]!
	vrhadd.u8 d2,d0,d1
	vst1.8 {d2},[r8]!
	add r12,#8
	cmp r12,r6
	bne avg_pel_rect8_x

	add r0,r0,r1
	add r2,r2,r3
	add r4,r4,r5
	sub r7,r7,#1
	cmp r7,#0
	bne avg_pel_rect8_y

	b end_avg_pel_rect

avg_pel_rect16:

avg_pel_rect16_y:
	mov r8,r0
	mov r9,r2
	mov r10,r4
	mov r12,#0
avg_pel_rect16_x:
	vld1.8 {q0},[r9]!
	vld1.8 {q1},[r10]!
	vrhadd.u8 q2,q0,q1
	vst1.8 {q2},[r8]!
	add r12,#16
	cmp r12,r6
	bne avg_pel_rect16_x

	add r0,r0,r1
	add r2,r2,r3
	add r4,r4,r5
	sub r7,r7,#1
	cmp r7,#0
	bne avg_pel_rect16_y

end_avg_pel_rect:
	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	mov pc, lr


function uavs3d_padding_rows_lr_armv7
@p->r0, i_src->r1, width->r2, rows->r3, padh->r4;

	stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	add sp, sp, #40
	ldmia sp, {r4}
	sub sp, sp, #40
	sub r7, r2, #1    @ width - 1

padding_rows_lr_y:
	mov r8, #0

	ldrb r12, [r0]   @ p[0]
	vdup.8 q0, r12

	add r5, r0, r7   @ p[width - 1]
	ldrb r12, [r5]
	vdup.8 q1, r12

	sub r5, r0, r4
	add r6, r0, r2

	sub r9, r4, #15

padding_rows_lr_x: 

	vst1.8 {q0},[r5]!
	vst1.8 {q1},[r6]!

	add r8,#16
	cmp r8, r9
	blt padding_rows_lr_x

	cmp r8, r4
	beq padding_rows_lr_loop
	vst1.8 {d0},[r5]
	vst1.8 {d2},[r6]

padding_rows_lr_loop:
	add r0,r0,r1
	sub r3,#1
	cmp r3,#0
	bne padding_rows_lr_y

	ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
	mov pc, lr

function uavs3d_padding_rows_chroma_lr_armv7
    @p->r0, i_src->r1, width->r2, rows->r3, padh->r4;
    
    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    add sp, sp, #40
    ldmia sp, {r4}
    sub sp, sp, #40
    sub r7, r2, #2    @ width - 2
    
    padding_rows_chroma_lr_y:
    mov r8, #0
    
    ldrh r12, [r0]   @ p[0] p[1]
    vdup.16 q0, r12
    
    add r5, r0, r7   @ p[width - 2] p[width - 1]
    ldrh r12, [r5]
    vdup.16 q1, r12
    
    sub r5, r0, r4
    add r6, r0, r2
    
    sub r9, r4, #15
    
    padding_rows_chroma_lr_x:
    
    vst1.16 {q0},[r5]!
    vst1.16 {q1},[r6]!
    
    add r8,#16
    cmp r8, r9
    blt padding_rows_chroma_lr_x
    
    cmp r8, r4
    beq padding_rows_chroma_lr_loop
    vst1.16 {d0},[r5]
    vst1.16 {d2},[r6]
    
    padding_rows_chroma_lr_loop:
    add r0,r0,r1
    sub r3,#1
    cmp r3,#0
    bne padding_rows_chroma_lr_y
    
    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    mov pc, lr

//void uavs3d_conv_fmt_8bit_armv7(unsigned char* src_y, unsigned char* src_uv, unsigned char* dst[3], int width, int height, int src_stride, int src_stridec, int dst_stride[3], int uv_shift);
function uavs3d_conv_fmt_8bit_armv7
@src_y->r0, src_uv->r1, dst->r2, width->r3, height->r4, stride->r5, stridec->r6, dst_stride->r7, uv_shift->r8

    stmdb sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    add sp, sp, #40
    ldmia sp, {r4, r5, r6, r7, r8}
    sub sp, sp, #40

    and r11, r3, #63            // width % 64
    and r9 , r3, #15            // width % 16
    sub r10, r3, r11            // width64 = width - (width % 64)
    sub r12, r3, r9             // width16 = width - (width % 16)

    push {r1, r2, r6, r7, r8}

    mov r8, #0                  // i = 0
    ldr r2, [r2]                // pdst = dst[0]
    ldr r6, [r7]                // r6 = dst_stride[0]
copy_y_height_loop:
    mov r9, #0                  // j = 0
    mov r11, r0
    mov r1, r2
copy_y_width_loop64:
    add r7, r9, #64
    cmp r7, r10
bgt copy_y_width_loop16
    vld1.8 {q0, q1}, [r11]!
    mov r9, r7                  // j += 64
    vld1.8 {q2, q3}, [r11]!
    vst1.8 {q0, q1}, [r1]!
    vst1.8 {q2, q3}, [r1]!
    b copy_y_width_loop64

copy_y_width_loop16:
    add r7, r9, #16
    cmp r7, r12
bgt copy_y_width_loop1
    vld1.8 {q0}, [r11]!
    mov r9, r7
    vst1.8 {q0}, [r1]!
    b copy_y_width_loop16

copy_y_width_loop1:
    cmp r9, r3
    bge copy_y_width_end
    ldrb r7, [r11], #1
    add r9, r9, #1
    strb r7, [r1], #1
    b copy_y_width_loop1

copy_y_width_end:

    add r8, r8, #1
    add r0, r0, r5
    add r2, r2, r6
    cmp r8, r4
    blt copy_y_height_loop

    pop {r1, r2, r6, r7, r8}

    lsr r3, r3, r8              // width >>= uv_shift
    lsr r4, r4, r8              // height >>= uv_shift

    push {r1, r2, r7}

    and r8, r3, #31             // width % 32
    and r9, r3, #7              // width % 8
    sub r10, r3, r8             // width32 = width - (width % 32)
    sub r12, r3, r9             // width8  = width - (width % 8)

    mov r0, r1                  // src = src_uv
    ldr r2, [r2, #4]            // pdst = dst[1]
    ldr r5, [r7, #4]            // r5 = dst_stride[1]
    mov r8, #0                  // i = 0
copy_u_height_loop:
    mov r9, #0                  // j = 0
    mov r7, #0
    mov r11, r0
    mov r1, r2
copy_u_width_loop32:
    add r7, r9, #32
    cmp r7, r10
    bgt copy_u_width_loop8
    vld1.16 {q0, q1}, [r11]!
    mov r9, r7                  // j += 32
    vld1.8 {q2, q3}, [r11]!
    vmovn.i16 d0, q0
    vmovn.i16 d1, q1
    vmovn.i16 d2, q2
    vmovn.i16 d3, q3

    vst1.8 {q0, q1}, [r1]!
    b copy_u_width_loop32

copy_u_width_loop8:
    add r7, r9, #8
    cmp r7, r12
    bgt copy_u_width_loop1
    vld1.16 {q0}, [r11]!
    mov r9, r7                  // j += 8
    vmovn.i16 d0, q0
    vst1.8 {d0}, [r1]!
    b copy_u_width_loop8

copy_u_width_loop1:
    cmp r9, r3
    bge copy_u_width_end
    ldrb r7, [r11], #2
    add r9, r9, #1
    strb r7, [r1], #1
    b copy_u_width_loop1

copy_u_width_end:
    add r8, r8, #1              // i++
    add r0, r0, r6              // src += stridec
    add r2, r2, r5              // pdst += dst_stride
    cmp r8, r4
    blt copy_u_height_loop

    pop {r1, r2, r7}

    add r0, r1, #1              // src = src_uv + 1
    ldr r2, [r2, #8]            // pdst = dst[2]
    ldr r5, [r7, #8]            // r5 = dst_stride[2]
    mov r8, #0                  // i = 0
copy_v_height_loop:
    mov r9, #0                  // j = 0
    mov r11, r0
    mov r1, r2
copy_v_width_loop32:
    add r7, r9, #32
    cmp r7, r10
bgt copy_v_width_loop8
    vld1.16 {q0, q1}, [r11]!
    mov r9, r7                  // j += 32
    vld1.8 {q2, q3}, [r11]!
    vmovn.i16 d0, q0
    vmovn.i16 d1, q1
    vmovn.i16 d2, q2
    vmovn.i16 d3, q3

    vst1.8 {q0, q1}, [r1]!
    b copy_v_width_loop32

copy_v_width_loop8:
    add r7, r9, #8
    cmp r7, r12
    bgt copy_v_width_loop1
    vld1.16 {q0}, [r11]!
    mov r9, r7                  // j += 8
    vmovn.i16 d0, q0
    vst1.8 {d0}, [r1]!
    b copy_v_width_loop8

copy_v_width_loop1:
    cmp r9, r3
    bge copy_v_width_end
    ldrb r7, [r11], #2
    add  r9, r9, #1
    strb r7, [r1], #1
    b copy_v_width_loop1

copy_v_width_end:
    add r8, r8, #1              // i++
    add r0, r0, r6              // src += stridec
    add r2, r2, r5
    cmp r8, r4
    blt copy_v_height_loop

    ldmia sp!, {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}
    mov pc, lr

#endif
