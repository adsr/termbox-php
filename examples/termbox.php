<?php

if (!extension_loaded('termbox')) {
    dl('termbox.' . PHP_SHLIB_SUFFIX);
}

if (!function_exists('termbox_init')) {
    fwrite(STDERR, "termbox module not found\n");
    exit(1);
}

function main() {
    if (!termbox_init()) {
        fwrite(STDERR, "termbox_init failed with error code " . termbox_last_error() . "\n");
        exit(1);
    }

    termbox_set_input_mode(TB_INPUT_ESC);

    termbox_clear();
    draw_keyboard();
    termbox_present();

    $ctrlxpressed = false;
    while (false !== ($ev = termbox_poll_event())) {
        switch ($ev['type']) {
            case TB_EVENT_KEY:
                if ($ev['key'] == TB_KEY_CTRL_Q && $ctrlxpressed) {
                    termbox_shutdown();
                    exit(0);
                } else if ($ev['key'] == TB_KEY_CTRL_C && $ctrlxpressed) {
                    $chmap = [0, 2, 1];
                    termbox_set_input_mode($chmap[termbox_get_input_mode()]);
                }
                $ctrlxpressed = $ev['key'] == TB_KEY_CTRL_X;
                termbox_clear();
                draw_keyboard();
                dispatch_press($ev);
                pretty_print_press($ev);
                termbox_present();
                break;
            case TB_EVENT_RESIZE:
                termbox_clear();
                draw_keyboard();
                pretty_print_resize($ev);
                termbox_present();
                break;
            default:
                break;
        }
    }

    termbox_shutdown();
}

$K_ESC = [[1,1,'E'],[2,1,'S'],[3,1,'C']];
$K_F1 = [[6,1,'F'],[7,1,'1']];
$K_F2 = [[9,1,'F'],[10,1,'2']];
$K_F3 = [[12,1,'F'],[13,1,'3']];
$K_F4 = [[15,1,'F'],[16,1,'4']];
$K_F5 = [[19,1,'F'],[20,1,'5']];
$K_F6 = [[22,1,'F'],[23,1,'6']];
$K_F7 = [[25,1,'F'],[26,1,'7']];
$K_F8 = [[28,1,'F'],[29,1,'8']];
$K_F9 = [[33,1,'F'],[34,1,'9']];
$K_F10 = [[36,1,'F'],[37,1,'1'],[38,1,'0']];
$K_F11 = [[40,1,'F'],[41,1,'1'],[42,1,'1']];
$K_F12 = [[44,1,'F'],[45,1,'1'],[46,1,'2']];
$K_PRN = [[50,1,'P'],[51,1,'R'],[52,1,'N']];
$K_SCR = [[54,1,'S'],[55,1,'C'],[56,1,'R']];
$K_BRK = [[58,1,'B'],[59,1,'R'],[60,1,'K']];
$K_LED1 = [[66,1,'-']];
$K_LED2 = [[70,1,'-']];
$K_LED3 = [[74,1,'-']];

$K_TILDE = [[1,4,'`']];
$K_TILDE_SHIFT = [[1,4,'~']];
$K_1 = [[4,4,'1']];
$K_1_SHIFT = [[4,4,'!']];
$K_2 = [[7,4,'2']];
$K_2_SHIFT = [[7,4,'@']];
$K_3 = [[10,4,'3']];
$K_3_SHIFT = [[10,4,'#']];
$K_4 = [[13,4,'4']];
$K_4_SHIFT = [[13,4,'$']];
$K_5 = [[16,4,'5']];
$K_5_SHIFT = [[16,4,'%']];
$K_6 = [[19,4,'6']];
$K_6_SHIFT = [[19,4,'^']];
$K_7 = [[22,4,'7']];
$K_7_SHIFT = [[22,4,'&']];
$K_8 = [[25,4,'8']];
$K_8_SHIFT = [[25,4,'*']];
$K_9 = [[28,4,'9']];
$K_9_SHIFT = [[28,4,'(']];
$K_0 = [[31,4,'0']];
$K_0_SHIFT = [[31,4,')']];
$K_MINUS = [[34,4,'-']];
$K_MINUS_SHIFT = [[34,4,'_']];
$K_EQUALS = [[37,4,'=']];
$K_EQUALS_SHIFT = [[37,4,'+']];
$K_BACKSLASH = [[40,4,'\\']];
$K_BACKSLASH_SHIFT = [[40,4,'|']];
$K_BACKSPACE = [[44,4,0x2190],[45,4,0x2500],[46,4,0x2500]];
$K_INS = [[50,4,'I'],[51,4,'N'],[52,4,'S']];
$K_HOM = [[54,4,'H'],[55,4,'O'],[56,4,'M']];
$K_PGU = [[58,4,'P'],[59,4,'G'],[60,4,'U']];
$K_K_NUMLOCK = [[65,4,'N']];
$K_K_SLASH = [[68,4,'/']];
$K_K_STAR = [[71,4,'*']];
$K_K_MINUS = [[74,4,'-']];

$K_TAB = [[1,6,'T'],[2,6,'A'],[3,6,'B']];
$K_q = [[6,6,'q']];
$K_Q = [[6,6,'Q']];
$K_w = [[9,6,'w']];
$K_W = [[9,6,'W']];
$K_e = [[12,6,'e']];
$K_E = [[12,6,'E']];
$K_r = [[15,6,'r']];
$K_R = [[15,6,'R']];
$K_t = [[18,6,'t']];
$K_T = [[18,6,'T']];
$K_y = [[21,6,'y']];
$K_Y = [[21,6,'Y']];
$K_u = [[24,6,'u']];
$K_U = [[24,6,'U']];
$K_i = [[27,6,'i']];
$K_I = [[27,6,'I']];
$K_o = [[30,6,'o']];
$K_O = [[30,6,'O']];
$K_p = [[33,6,'p']];
$K_P = [[33,6,'P']];
$K_LSQB = [[36,6,'[']];
$K_LCUB = [[36,6,'{']];
$K_RSQB = [[39,6,']']];
$K_RCUB = [[39,6,'}']];
$K_ENTER = [
    [43,6,0x2591],[44,6,0x2591],[45,6,0x2591],[46,6,0x2591],
    [43,7,0x2591],[44,7,0x2591],[45,7,0x21B5],[46,7,0x2591],
    [41,8,0x2591],[42,8,0x2591],[43,8,0x2591],[44,8,0x2591],
    [45,8,0x2591],[46,8,0x2591]
];
$K_DEL = [[50,6,'D'],[51,6,'E'],[52,6,'L']];
$K_END = [[54,6,'E'],[55,6,'N'],[56,6,'D']];
$K_PGD = [[58,6,'P'],[59,6,'G'],[60,6,'D']];
$K_K_7 = [[65,6,'7']];
$K_K_8 = [[68,6,'8']];
$K_K_9 = [[71,6,'9']];
$K_K_PLUS = [[74,6,' '],[74,7,'+'],[74,8,' ']];

$K_CAPS = [[1,8,'C'],[2,8,'A'],[3,8,'P'],[4,8,'S']];
$K_a = [[7,8,'a']];
$K_A = [[7,8,'A']];
$K_s = [[10,8,'s']];
$K_S = [[10,8,'S']];
$K_d = [[13,8,'d']];
$K_D = [[13,8,'D']];
$K_f = [[16,8,'f']];
$K_F = [[16,8,'F']];
$K_g = [[19,8,'g']];
$K_G = [[19,8,'G']];
$K_h = [[22,8,'h']];
$K_H = [[22,8,'H']];
$K_j = [[25,8,'j']];
$K_J = [[25,8,'J']];
$K_k = [[28,8,'k']];
$K_K = [[28,8,'K']];
$K_l = [[31,8,'l']];
$K_L = [[31,8,'L']];
$K_SEMICOLON = [[34,8,';']];
$K_PARENTHESIS = [[34,8,':']];
$K_QUOTE = [[37,8,'\'']];
$K_DOUBLEQUOTE = [[37,8,'"']];
$K_K_4 = [[65,8,'4']];
$K_K_5 = [[68,8,'5']];
$K_K_6 = [[71,8,'6']];

$K_LSHIFT = [[1,10,'S'],[2,10,'H'],[3,10,'I'],[4,10,'F'],[5,10,'T']];
$K_z = [[9,10,'z']];
$K_Z = [[9,10,'Z']];
$K_x = [[12,10,'x']];
$K_X = [[12,10,'X']];
$K_c = [[15,10,'c']];
$K_C = [[15,10,'C']];
$K_v = [[18,10,'v']];
$K_V = [[18,10,'V']];
$K_b = [[21,10,'b']];
$K_B = [[21,10,'B']];
$K_n = [[24,10,'n']];
$K_N = [[24,10,'N']];
$K_m = [[27,10,'m']];
$K_M = [[27,10,'M']];
$K_COMMA = [[30,10,',']];
$K_LANB = [[30,10,'<']];
$K_PERIOD = [[33,10,'.']];
$K_RANB = [[33,10,'>']];
$K_SLASH = [[36,10,'/']];
$K_QUESTION = [[36,10,'?']];
$K_RSHIFT = [[42,10,'S'],[43,10,'H'],[44,10,'I'],[45,10,'F'],[46,10,'T']];
$K_ARROW_UP = [[54,10,'('],[55,10,0x2191],[56,10,')']];
$K_K_1 = [[65,10,'1']];
$K_K_2 = [[68,10,'2']];
$K_K_3 = [[71,10,'3']];
$K_K_ENTER = [[74,10,0x2591],[74,11,0x2591],[74,12,0x2591]];

$K_LCTRL = [[1,12,'C'],[2,12,'T'],[3,12,'R'],[4,12,'L']];
$K_LWIN = [[6,12,'W'],[7,12,'I'],[8,12,'N']];
$K_LALT = [[10,12,'A'],[11,12,'L'],[12,12,'T']];
$K_SPACE = [
    [14,12,' '],[15,12,' '],[16,12,' '],[17,12,' '],[18,12,' '],
    [19,12,'S'],[20,12,'P'],[21,12,'A'],[22,12,'C'],[23,12,'E'],
    [24,12,' '],[25,12,' '],[26,12,' '],[27,12,' '],[28,12,' '],
];
$K_RALT = [[30,12,'A'],[31,12,'L'],[32,12,'T']];
$K_RWIN = [[34,12,'W'],[35,12,'I'],[36,12,'N']];
$K_RPROP = [[38,12,'P'],[39,12,'R'],[40,12,'O'],[41,12,'P']];
$K_RCTRL = [[43,12,'C'],[44,12,'T'],[45,12,'R'],[46,12,'L']];
$K_ARROW_LEFT = [[50,12,'('],[51,12,0x2190],[52,12,')']];
$K_ARROW_DOWN = [[54,12,'('],[55,12,0x2193],[56,12,')']];
$K_ARROW_RIGHT = [[58,12,'('],[59,12,0x2192],[60,12,')']];
$K_K_0 = [[65,12,' '],[66,12,'0'],[67,12,' '],[68,12,' ']];
$K_K_PERIOD = [[71,12,'.']];

$combos = [
    [$K_TILDE, $K_2, $K_LCTRL, $K_RCTRL],
    [$K_A, $K_LCTRL, $K_RCTRL],
    [$K_B, $K_LCTRL, $K_RCTRL],
    [$K_C, $K_LCTRL, $K_RCTRL],
    [$K_D, $K_LCTRL, $K_RCTRL],
    [$K_E, $K_LCTRL, $K_RCTRL],
    [$K_F, $K_LCTRL, $K_RCTRL],
    [$K_G, $K_LCTRL, $K_RCTRL],
    [$K_H, $K_BACKSPACE, $K_LCTRL, $K_RCTRL],
    [$K_I, $K_TAB, $K_LCTRL, $K_RCTRL],
    [$K_J, $K_LCTRL, $K_RCTRL],
    [$K_K, $K_LCTRL, $K_RCTRL],
    [$K_L, $K_LCTRL, $K_RCTRL],
    [$K_M, $K_ENTER, $K_K_ENTER, $K_LCTRL, $K_RCTRL],
    [$K_N, $K_LCTRL, $K_RCTRL],
    [$K_O, $K_LCTRL, $K_RCTRL],
    [$K_P, $K_LCTRL, $K_RCTRL],
    [$K_Q, $K_LCTRL, $K_RCTRL],
    [$K_R, $K_LCTRL, $K_RCTRL],
    [$K_S, $K_LCTRL, $K_RCTRL],
    [$K_T, $K_LCTRL, $K_RCTRL],
    [$K_U, $K_LCTRL, $K_RCTRL],
    [$K_V, $K_LCTRL, $K_RCTRL],
    [$K_W, $K_LCTRL, $K_RCTRL],
    [$K_X, $K_LCTRL, $K_RCTRL],
    [$K_Y, $K_LCTRL, $K_RCTRL],
    [$K_Z, $K_LCTRL, $K_RCTRL],
    [$K_LSQB, $K_ESC, $K_3, $K_LCTRL, $K_RCTRL],
    [$K_4, $K_BACKSLASH, $K_LCTRL, $K_RCTRL],
    [$K_RSQB, $K_5, $K_LCTRL, $K_RCTRL],
    [$K_6, $K_LCTRL, $K_RCTRL],
    [$K_7, $K_SLASH, $K_MINUS_SHIFT, $K_LCTRL, $K_RCTRL],
    [$K_SPACE],
    [$K_1_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_DOUBLEQUOTE,$K_LSHIFT,$K_RSHIFT],
    [$K_3_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_4_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_5_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_7_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_QUOTE],
    [$K_9_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_0_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_8_SHIFT,$K_K_STAR,$K_LSHIFT,$K_RSHIFT],
    [$K_EQUALS_SHIFT,$K_K_PLUS,$K_LSHIFT,$K_RSHIFT],
    [$K_COMMA],
    [$K_MINUS,$K_K_MINUS],
    [$K_PERIOD,$K_K_PERIOD],
    [$K_SLASH,$K_K_SLASH],
    [$K_0,$K_K_0],
    [$K_1,$K_K_1],
    [$K_2,$K_K_2],
    [$K_3,$K_K_3],
    [$K_4,$K_K_4],
    [$K_5,$K_K_5],
    [$K_6,$K_K_6],
    [$K_7,$K_K_7],
    [$K_8,$K_K_8],
    [$K_9,$K_K_9],
    [$K_PARENTHESIS,$K_LSHIFT,$K_RSHIFT],
    [$K_SEMICOLON],
    [$K_LANB,$K_LSHIFT,$K_RSHIFT],
    [$K_EQUALS],
    [$K_RANB,$K_LSHIFT,$K_RSHIFT],
    [$K_QUESTION,$K_LSHIFT,$K_RSHIFT],
    [$K_2_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_A,$K_LSHIFT,$K_RSHIFT],
    [$K_B,$K_LSHIFT,$K_RSHIFT],
    [$K_C,$K_LSHIFT,$K_RSHIFT],
    [$K_D,$K_LSHIFT,$K_RSHIFT],
    [$K_E,$K_LSHIFT,$K_RSHIFT],
    [$K_F,$K_LSHIFT,$K_RSHIFT],
    [$K_G,$K_LSHIFT,$K_RSHIFT],
    [$K_H,$K_LSHIFT,$K_RSHIFT],
    [$K_I,$K_LSHIFT,$K_RSHIFT],
    [$K_J,$K_LSHIFT,$K_RSHIFT],
    [$K_K,$K_LSHIFT,$K_RSHIFT],
    [$K_L,$K_LSHIFT,$K_RSHIFT],
    [$K_M,$K_LSHIFT,$K_RSHIFT],
    [$K_N,$K_LSHIFT,$K_RSHIFT],
    [$K_O,$K_LSHIFT,$K_RSHIFT],
    [$K_P,$K_LSHIFT,$K_RSHIFT],
    [$K_Q,$K_LSHIFT,$K_RSHIFT],
    [$K_R,$K_LSHIFT,$K_RSHIFT],
    [$K_S,$K_LSHIFT,$K_RSHIFT],
    [$K_T,$K_LSHIFT,$K_RSHIFT],
    [$K_U,$K_LSHIFT,$K_RSHIFT],
    [$K_V,$K_LSHIFT,$K_RSHIFT],
    [$K_W,$K_LSHIFT,$K_RSHIFT],
    [$K_X,$K_LSHIFT,$K_RSHIFT],
    [$K_Y,$K_LSHIFT,$K_RSHIFT],
    [$K_Z,$K_LSHIFT,$K_RSHIFT],
    [$K_LSQB],
    [$K_BACKSLASH],
    [$K_RSQB],
    [$K_6_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_MINUS_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_TILDE],
    [$K_a],
    [$K_b],
    [$K_c],
    [$K_d],
    [$K_e],
    [$K_f],
    [$K_g],
    [$K_h],
    [$K_i],
    [$K_j],
    [$K_k],
    [$K_l],
    [$K_m],
    [$K_n],
    [$K_o],
    [$K_p],
    [$K_q],
    [$K_r],
    [$K_s],
    [$K_t],
    [$K_u],
    [$K_v],
    [$K_w],
    [$K_x],
    [$K_y],
    [$K_z],
    [$K_LCUB,$K_LSHIFT,$K_RSHIFT],
    [$K_BACKSLASH_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_RCUB,$K_LSHIFT,$K_RSHIFT],
    [$K_TILDE_SHIFT,$K_LSHIFT,$K_RSHIFT],
    [$K_8, $K_BACKSPACE, $K_LCTRL, $K_RCTRL]
];

$func_combos = [
    [$K_F1],
    [$K_F2],
    [$K_F3],
    [$K_F4],
    [$K_F5],
    [$K_F6],
    [$K_F7],
    [$K_F8],
    [$K_F9],
    [$K_F10],
    [$K_F11],
    [$K_F12],
    [$K_INS],
    [$K_DEL],
    [$K_HOM],
    [$K_END],
    [$K_PGU],
    [$K_PGD],
    [$K_ARROW_UP],
    [$K_ARROW_DOWN],
    [$K_ARROW_LEFT],
    [$K_ARROW_RIGHT]
];

function printf_tb($x, $y, $fg, $bg, $fmt) {
    $buf = vsprintf($fmt, array_slice(func_get_args(), 5));
    termbox_print($buf, $x, $y, $fg, $bg);
}

function draw_key($ks, $fg, $bg) {
    foreach ($ks as $k) {
        termbox_change_cell($k[0]+2, $k[1]+4, is_int($k[2]) ? $k[2] : ord($k[2]), $fg, $bg);
    }
}

function draw_keyboard() {
    extract($GLOBALS);
    termbox_change_cell(0, 0, 0x250C, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(79, 0, 0x2510, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(0, 23, 0x2514, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(79, 23, 0x2518, TB_WHITE, TB_DEFAULT);

    for ($i = 1; $i < 79; ++$i) {
        termbox_change_cell($i, 0, 0x2500, TB_WHITE, TB_DEFAULT);
        termbox_change_cell($i, 23, 0x2500, TB_WHITE, TB_DEFAULT);
        termbox_change_cell($i, 17, 0x2500, TB_WHITE, TB_DEFAULT);
        termbox_change_cell($i, 4, 0x2500, TB_WHITE, TB_DEFAULT);
    }
    for ($i = 1; $i < 23; ++$i) {
        termbox_change_cell(0, $i, 0x2502, TB_WHITE, TB_DEFAULT);
        termbox_change_cell(79, $i, 0x2502, TB_WHITE, TB_DEFAULT);
    }
    termbox_change_cell(0, 17, 0x251C, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(79, 17, 0x2524, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(0, 4, 0x251C, TB_WHITE, TB_DEFAULT);
    termbox_change_cell(79, 4, 0x2524, TB_WHITE, TB_DEFAULT);
    for ($i = 5; $i < 17; ++$i) {
        termbox_change_cell(1, $i, 0x2588, TB_YELLOW, TB_YELLOW);
        termbox_change_cell(78, $i, 0x2588, TB_YELLOW, TB_YELLOW);
    }

    draw_key($K_ESC, TB_WHITE, TB_BLUE);
    draw_key($K_F1, TB_WHITE, TB_BLUE);
    draw_key($K_F2, TB_WHITE, TB_BLUE);
    draw_key($K_F3, TB_WHITE, TB_BLUE);
    draw_key($K_F4, TB_WHITE, TB_BLUE);
    draw_key($K_F5, TB_WHITE, TB_BLUE);
    draw_key($K_F6, TB_WHITE, TB_BLUE);
    draw_key($K_F7, TB_WHITE, TB_BLUE);
    draw_key($K_F8, TB_WHITE, TB_BLUE);
    draw_key($K_F9, TB_WHITE, TB_BLUE);
    draw_key($K_F10, TB_WHITE, TB_BLUE);
    draw_key($K_F11, TB_WHITE, TB_BLUE);
    draw_key($K_F12, TB_WHITE, TB_BLUE);
    draw_key($K_PRN, TB_WHITE, TB_BLUE);
    draw_key($K_SCR, TB_WHITE, TB_BLUE);
    draw_key($K_BRK, TB_WHITE, TB_BLUE);
    draw_key($K_LED1, TB_WHITE, TB_BLUE);
    draw_key($K_LED2, TB_WHITE, TB_BLUE);
    draw_key($K_LED3, TB_WHITE, TB_BLUE);

    draw_key($K_TILDE, TB_WHITE, TB_BLUE);
    draw_key($K_1, TB_WHITE, TB_BLUE);
    draw_key($K_2, TB_WHITE, TB_BLUE);
    draw_key($K_3, TB_WHITE, TB_BLUE);
    draw_key($K_4, TB_WHITE, TB_BLUE);
    draw_key($K_5, TB_WHITE, TB_BLUE);
    draw_key($K_6, TB_WHITE, TB_BLUE);
    draw_key($K_7, TB_WHITE, TB_BLUE);
    draw_key($K_8, TB_WHITE, TB_BLUE);
    draw_key($K_9, TB_WHITE, TB_BLUE);
    draw_key($K_0, TB_WHITE, TB_BLUE);
    draw_key($K_MINUS, TB_WHITE, TB_BLUE);
    draw_key($K_EQUALS, TB_WHITE, TB_BLUE);
    draw_key($K_BACKSLASH, TB_WHITE, TB_BLUE);
    draw_key($K_BACKSPACE, TB_WHITE, TB_BLUE);
    draw_key($K_INS, TB_WHITE, TB_BLUE);
    draw_key($K_HOM, TB_WHITE, TB_BLUE);
    draw_key($K_PGU, TB_WHITE, TB_BLUE);
    draw_key($K_K_NUMLOCK, TB_WHITE, TB_BLUE);
    draw_key($K_K_SLASH, TB_WHITE, TB_BLUE);
    draw_key($K_K_STAR, TB_WHITE, TB_BLUE);
    draw_key($K_K_MINUS, TB_WHITE, TB_BLUE);

    draw_key($K_TAB, TB_WHITE, TB_BLUE);
    draw_key($K_q, TB_WHITE, TB_BLUE);
    draw_key($K_w, TB_WHITE, TB_BLUE);
    draw_key($K_e, TB_WHITE, TB_BLUE);
    draw_key($K_r, TB_WHITE, TB_BLUE);
    draw_key($K_t, TB_WHITE, TB_BLUE);
    draw_key($K_y, TB_WHITE, TB_BLUE);
    draw_key($K_u, TB_WHITE, TB_BLUE);
    draw_key($K_i, TB_WHITE, TB_BLUE);
    draw_key($K_o, TB_WHITE, TB_BLUE);
    draw_key($K_p, TB_WHITE, TB_BLUE);
    draw_key($K_LSQB, TB_WHITE, TB_BLUE);
    draw_key($K_RSQB, TB_WHITE, TB_BLUE);
    draw_key($K_ENTER, TB_WHITE, TB_BLUE);
    draw_key($K_DEL, TB_WHITE, TB_BLUE);
    draw_key($K_END, TB_WHITE, TB_BLUE);
    draw_key($K_PGD, TB_WHITE, TB_BLUE);
    draw_key($K_K_7, TB_WHITE, TB_BLUE);
    draw_key($K_K_8, TB_WHITE, TB_BLUE);
    draw_key($K_K_9, TB_WHITE, TB_BLUE);
    draw_key($K_K_PLUS, TB_WHITE, TB_BLUE);

    draw_key($K_CAPS, TB_WHITE, TB_BLUE);
    draw_key($K_a, TB_WHITE, TB_BLUE);
    draw_key($K_s, TB_WHITE, TB_BLUE);
    draw_key($K_d, TB_WHITE, TB_BLUE);
    draw_key($K_f, TB_WHITE, TB_BLUE);
    draw_key($K_g, TB_WHITE, TB_BLUE);
    draw_key($K_h, TB_WHITE, TB_BLUE);
    draw_key($K_j, TB_WHITE, TB_BLUE);
    draw_key($K_k, TB_WHITE, TB_BLUE);
    draw_key($K_l, TB_WHITE, TB_BLUE);
    draw_key($K_SEMICOLON, TB_WHITE, TB_BLUE);
    draw_key($K_QUOTE, TB_WHITE, TB_BLUE);
    draw_key($K_K_4, TB_WHITE, TB_BLUE);
    draw_key($K_K_5, TB_WHITE, TB_BLUE);
    draw_key($K_K_6, TB_WHITE, TB_BLUE);

    draw_key($K_LSHIFT, TB_WHITE, TB_BLUE);
    draw_key($K_z, TB_WHITE, TB_BLUE);
    draw_key($K_x, TB_WHITE, TB_BLUE);
    draw_key($K_c, TB_WHITE, TB_BLUE);
    draw_key($K_v, TB_WHITE, TB_BLUE);
    draw_key($K_b, TB_WHITE, TB_BLUE);
    draw_key($K_n, TB_WHITE, TB_BLUE);
    draw_key($K_m, TB_WHITE, TB_BLUE);
    draw_key($K_COMMA, TB_WHITE, TB_BLUE);
    draw_key($K_PERIOD, TB_WHITE, TB_BLUE);
    draw_key($K_SLASH, TB_WHITE, TB_BLUE);
    draw_key($K_RSHIFT, TB_WHITE, TB_BLUE);
    draw_key($K_ARROW_UP, TB_WHITE, TB_BLUE);
    draw_key($K_K_1, TB_WHITE, TB_BLUE);
    draw_key($K_K_2, TB_WHITE, TB_BLUE);
    draw_key($K_K_3, TB_WHITE, TB_BLUE);
    draw_key($K_K_ENTER, TB_WHITE, TB_BLUE);

    draw_key($K_LCTRL, TB_WHITE, TB_BLUE);
    draw_key($K_LWIN, TB_WHITE, TB_BLUE);
    draw_key($K_LALT, TB_WHITE, TB_BLUE);
    draw_key($K_SPACE, TB_WHITE, TB_BLUE);
    draw_key($K_RCTRL, TB_WHITE, TB_BLUE);
    draw_key($K_RPROP, TB_WHITE, TB_BLUE);
    draw_key($K_RWIN, TB_WHITE, TB_BLUE);
    draw_key($K_RALT, TB_WHITE, TB_BLUE);
    draw_key($K_ARROW_LEFT, TB_WHITE, TB_BLUE);
    draw_key($K_ARROW_DOWN, TB_WHITE, TB_BLUE);
    draw_key($K_ARROW_RIGHT, TB_WHITE, TB_BLUE);
    draw_key($K_K_0, TB_WHITE, TB_BLUE);
    draw_key($K_K_PERIOD, TB_WHITE, TB_BLUE);

    printf_tb(33, 1, TB_MAGENTA | TB_BOLD, TB_DEFAULT, "Keyboard demo!");
    printf_tb(21, 2, TB_MAGENTA, TB_DEFAULT, "(press CTRL+X and then CTRL+Q to exit)");
    printf_tb(15, 3, TB_MAGENTA, TB_DEFAULT, "(press CTRL+X and then CTRL+C to change input mode)");

    $inputmodemap = [
        '0',
        "TB_INPUT_ESC",
        "TB_INPUT_ALT"
    ];
    printf_tb(3, 18, TB_WHITE, TB_DEFAULT, "Input mode: %s",
            $inputmodemap[termbox_get_input_mode()]);
}

function funckeymap($k) {
    $fcmap = [
        "CTRL+2, CTRL+~",
        "CTRL+A",
        "CTRL+B",
        "CTRL+C",
        "CTRL+D",
        "CTRL+E",
        "CTRL+F",
        "CTRL+G",
        "CTRL+H, BACKSPACE",
        "CTRL+I, TAB",
        "CTRL+J",
        "CTRL+K",
        "CTRL+L",
        "CTRL+M, ENTER",
        "CTRL+N",
        "CTRL+O",
        "CTRL+P",
        "CTRL+Q",
        "CTRL+R",
        "CTRL+S",
        "CTRL+T",
        "CTRL+U",
        "CTRL+V",
        "CTRL+W",
        "CTRL+X",
        "CTRL+Y",
        "CTRL+Z",
        "CTRL+3, ESC, CTRL+[",
        "CTRL+4, CTRL+\\",
        "CTRL+5, CTRL+]",
        "CTRL+6",
        "CTRL+7, CTRL+/, CTRL+_",
        "SPACE"
    ];
    $fkmap = [
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "INSERT",
        "DELETE",
        "HOME",
        "END",
        "PGUP",
        "PGDN",
        "ARROW UP",
        "ARROW DOWN",
        "ARROW LEFT",
        "ARROW RIGHT"
    ];

    if ($k == TB_KEY_CTRL_8)
        return "CTRL+8, BACKSPACE 2"; /* 0x7F */
    else if ($k >= TB_KEY_ARROW_RIGHT && $k <= 0xFFFF)
        return $fkmap[0xFFFF-$k];
    else if ($k <= TB_KEY_SPACE)
        return $fcmap[$k];
    return "UNKNOWN";
}

function pretty_print_press($ev) {
    $buf = termbox_utf8_unicode_to_char($ev['ch']);

    printf_tb(3, 19, TB_WHITE , TB_DEFAULT, "Key: ");
    printf_tb(8, 19, TB_YELLOW, TB_DEFAULT, "decimal: %d", $ev['key']);
    printf_tb(8, 20, TB_GREEN , TB_DEFAULT, "hex:     0x%X", $ev['key']);
    printf_tb(8, 21, TB_CYAN  , TB_DEFAULT, "octal:   0%o", $ev['key']);
    printf_tb(8, 22, TB_RED   , TB_DEFAULT, "string:  %s", funckeymap($ev['key']));

    printf_tb(43, 19, TB_WHITE , TB_DEFAULT, "Char: ");
    printf_tb(49, 19, TB_YELLOW, TB_DEFAULT, "decimal: %d", $ev['ch']);
    printf_tb(49, 20, TB_GREEN , TB_DEFAULT, "hex:     0x%X", $ev['ch']);
    printf_tb(49, 21, TB_CYAN  , TB_DEFAULT, "octal:   0%o", $ev['ch']);
    printf_tb(49, 22, TB_RED   , TB_DEFAULT, "string:  %s", $buf);

    printf_tb(43, 18, TB_WHITE, TB_DEFAULT, "Modifier: %s",
        ($ev['mod']) ? "TB_MOD_ALT" : "none");
}

function pretty_print_resize($ev) {
    printf_tb(3, 19, TB_WHITE, TB_DEFAULT, "Resize event: %d x %d", $ev['w'], $ev['h']);
}

function dispatch_press($ev) {
    extract($GLOBALS);
    if ($ev['mod'] & TB_MOD_ALT) {
        draw_key($K_LALT, TB_WHITE, TB_RED);
        draw_key($K_RALT, TB_WHITE, TB_RED);
    }
    $k = null;
    if ($ev['key'] >= TB_KEY_ARROW_RIGHT) {
        $k = $func_combos[0xFFFF - $ev['key']];
    } else if ($ev['ch'] < 128) {
        if ($ev['ch'] == 0 && $ev['key'] < 128) {
            $k = $combos[$ev['key']];
        } else {
            $k = $combos[$ev['ch']];
        }
    }
    if (!$k) {
        return;
    }
    foreach ($k as $key) {
        draw_key($key, TB_WHITE, TB_RED);
    }
}

main();
