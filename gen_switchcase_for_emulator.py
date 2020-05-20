FILENAME = "opcodes.h"

nop = """case {}:
    break;"""

lxi = """case {}:
    inst_siz = lxi(state, &state->{}, &state->{});
    break;"""
lxi_sp = """case {}:
    inst_siz = lxi(state, ((uint8_t *)&state->sp)+1,
                   (uint8_t *)&state->sp);
    break;"""

stax = """case {}:
    inst_siz = stax(state, state->{}, state->{});
    break;"""

inx = """case {}:
    inst_siz = inx(&state->{}, &state->{});
    break;"""
inx_sp = """case {}:
    inst_siz = inx(((uint8_t *)&state->sp)+1, (uint8_t *)&state->sp);
    break;"""

inr = """case {}:
    inst_siz = inr(state, &state->{});
    break;"""
inr_m = """case {}:
    inst_siz = inr(state, &state->memory[(state->h << 8) + state->l]);
    break;"""

dcr = """case {}:
    inst_siz = dcr(state, &state->{});
    break;"""
dcr_m = """case {}:
    inst_siz = dcr(state, &state->memory[(state->h << 8) + state->l]);
    break;"""

mvi = """case {}:
    inst_siz = mvi(state, &state->{});
    break;"""
mvi_m = """case {}:
    inst_siz = mvi(state, &state->memory[(state->h << 8) + state->l]);
    break;"""

rlc = """case {}:
    inst_siz = rlc(state);
    break;"""

dad = """case {}:
    inst_siz = dad(state, state->{}, state->{});
    break;"""
dad_sp = """case {}:
    inst_siz = dad(state, *(((uint8_t *)&state->sp)+1),
                   *(uint8_t *)&state->sp);
    break;"""

ldax = """case {}:
    inst_siz = ldax(state, state->{}, state->{});
    break;"""

dcx = """case {}:
    inst_siz = dcx(&state->{}, &state->{});
    break;"""
dcx_sp = """case {}:
    inst_siz = dcx(((uint8_t *)&state->sp)+1, (uint8_t *)&state->sp);
    break;"""

rrc = """case {}:
    inst_siz = rrc(state);
    break;"""

ral = """case {}:
    inst_siz = ral(state);
    break;"""

rar = """case {}:
    inst_siz = rar(state);
    break;"""

shld = """case {}:
    inst_siz = shld(state);
    break;"""

daa = """case {}:
    inst_siz = daa(state);
    break;"""

lhld = """case {}:
    inst_siz = lhld(state);
    break;"""

cma = """case {}:
    inst_siz = cma(state);
    break;"""

sta = """case {}:
    inst_siz = sta(state);
    break;"""

stc = """case {}:
    inst_siz = stc(state);
    break;"""

lda = """case {}:
    inst_siz = lda(state);
    break;"""

cmc = """case {}:
    inst_siz = cmc(state);
    break;"""

mov = """case {}:
    inst_siz = mov(&state->{}, state->{});
    break;"""
mov_m_x = """case {}:
    inst_siz = mov(&state->memory[state->h << 8 | state->l],
                   state->{});
    break;"""
mov_x_m = """case {}:
    inst_siz = mov(&state->{}, 
                   state->memory[state->h << 8 | state->l]);
    break;"""

hlt = """case {}:
    inst_siz = hlt(state);
    break;"""

add = """case {}:
    inst_siz = add(state, state->{});
    break;"""
add_m = """case {}:
    inst_siz = add(state, state->memory[state->h << 8 | state->l]);
    break;"""

adc = """case {}:
    inst_siz = adc(state, state->{});
    break;"""
adc_m = """case {}:
    inst_siz = adc(state, state->memory[state->h << 8 | state->l]);
    break;"""

sub = """case {}:
    inst_siz = sub(state, state->{});
    break;"""
sub_m = """case {}:
    inst_siz = sub(state, state->memory[state->h << 8 | state->l]);
    break;"""

sbb = """case {}:
    inst_siz = sbb(state, state->{});
    break;"""
sbb_m = """case {}:
    inst_siz = sbb(state, state->memory[state->h << 8 | state->l]);
    break;"""

ana = """case {}:
    inst_siz = ana(state, state->{});
    break;"""
ana_m = """case {}:
    inst_siz = ana(state, state->memory[state->h << 8 | state->l]);
    break;"""

xra = """case {}:
    inst_siz = xra(state, state->{});
    break;"""
xra_m = """case {}:
    inst_siz = xra(state, state->memory[state->h << 8 | state->l]);
    break;"""

ora = """case {}:
    inst_siz = ora(state, state->{});
    break;"""
ora_m = """case {}:
    inst_siz = ora(state, state->memory[state->h << 8 | state->l]);
    break;"""

_cmp = """case {}:
    inst_siz = cmp(state, state->{});
    break;"""
cmp_m = """case {}:
    inst_siz = cmp(state, state->memory[state->h << 8 | state->l]);
    break;"""

rnz = """case {}:
    inst_siz = rnz(state);
    break;"""

pop = """case {}:
    inst_siz = pop(state, &state->{}, &state->{});
    break;"""
pop_psw = """case {}:
    inst_siz = pop(state, (uint8_t *)&state->flags, &state->a);
    break;"""

jnz = """case {}:
    inst_siz = jnz(state);
    break;"""

jmp = """case {}:
    inst_siz = jmp(state);
    break;"""

cnz = """case {}:
    inst_siz = cnz(state);
    break;"""

push = """case {}:
    inst_siz = push(state, state->{}, state->{});
    break;"""
push_psw = """case {}:
    inst_siz = push(state, *(uint8_t *)&state->flags, state->a);
    break;"""

adi = """case {}:
    inst_siz = adi(state);
    break;"""

rst = """case {}:
    inst_siz = rst(state, {});
    break;"""

rz = """case {}:
    inst_siz = rz(state);
    break;"""

ret = """case {}:
    inst_siz = ret(state);
    break;"""

jz = """case {}:
    inst_siz = jz(state);
    break;"""

cz = """case {}:
    inst_siz = cz(state);
    break;"""

call = """case {}:
    inst_siz = call(state);
    break;"""

aci = """case {}:
    inst_siz = aci(state);
    break;"""

rnc = """case {}:
    inst_siz = rnc(state);
    break;"""

jnc = """case {}:
    inst_siz = jnc(state);
    break;"""

out = """case {}:
    inst_siz = out(state);
    break;"""

cnc = """case {}:
    inst_siz = cnc(state);
    break;"""

sui = """case {}:
    inst_siz = sui(state);
    break;"""

rc = """case {}:
    inst_siz = rc(state);
    break;"""

jc = """case {}:
    inst_siz = jc(state);
    break;"""

_in = """case {}:
    inst_siz = in(state);
    break;"""

cc = """case {}:
    inst_siz = cc(state);
    break;"""

sbi = """case {}:
    inst_siz = sbi(state);
    break;"""

rpo = """case {}:
    inst_siz = rpo(state);
    break;"""

jpo = """case {}:
    inst_siz = jpo(state);
    break;"""

xthl = """case {}:
    inst_siz = xthl(state);
    break;"""

cpo = """case {}:
    inst_siz = cpo(state);
    break;"""

ani = """case {}:
    inst_siz = ani(state);
    break;"""

rpe = """case {}:
    inst_siz = rpe(state);
    break;"""

pchl = """case {}:
    inst_siz = pchl(state);
    break;"""

jpe = """case {}:
    inst_siz = jpe(state);
    break;"""

xchg = """case {}:
    inst_siz = xchg(state);
    break;"""

cpe = """case {}:
    inst_siz = cpe(state);
    break;"""

xri = """case {}:
    inst_siz = xri(state);
    break;"""

rp = """case {}:
    inst_siz = rp(state);
    break;"""

jp = """case {}:
    inst_siz = jp(state);
    break;"""

di = """case {}:
    inst_siz = di(state);
    break;"""

cp = """case {}:
    inst_siz = cp(state);
    break;"""

ori = """case {}:
    inst_siz = ori(state);
    break;"""

rm = """case {}:
    inst_siz = rm(state);
    break;"""

sphl = """case {}:
    inst_siz = sphl(state);
    break;"""

jm = """case {}:
    inst_siz = jm(state);
    break;"""

ei = """case {}:
    inst_siz = ei(state);
    break;"""

cm = """case {}:
    inst_siz = cm(state);
    break;"""

cpi = """case {}:
    inst_siz = cpi(state);
    break;"""

default = """default:
    unimplemented_inst(state);
    break;"""

DATA = ["d8", "d16"]

if __name__ == "__main__":
    # parsing these ~100 templates above is a pain in the ass but rewriting
    # them would be even more annoying, thats why the code is so convoluted
    lines = []
    with open(FILENAME, "r") as f:
        lines = f.readlines()
    lines = filter(lambda x: x.startswith("#define "), lines)
    lines = map(lambda x: x.split()[1], lines)
    lines = filter(lambda x: "OPCODE" in x, lines)
    print("switch (inst) {")

    for macro in lines:
        parts = [part.lower() for part in macro.split("_")[1:]]
        if not parts:
            continue
        if any(map(lambda x: x in DATA + ["psw", "x", "m", "sp"], parts[1:])):
            if len(parts) == 2:
                if parts[1] in DATA:
                    try:
                        fmt = globals()[parts[0]]
                    except KeyError:
                        fmt = globals()["_" + parts[0]]
                    print(fmt.format(macro))
                elif parts[1] in ['psw', 'm', 'sp']:
                    fmt = globals()[parts[0] + f"_{parts[1]}"]
                    print(fmt.format(macro))
                else:
                    raise Exception
            elif len(parts) == 3:
                if parts[2] in DATA:
                    if parts[1] in ["sp", "m"]:
                        fmt = globals()[parts[0] + f"_{parts[1]}"]
                        print(fmt.format(macro))
                    else:
                        second_arg = chr(ord(parts[1])+1) if \
                                parts[1] != "h" else "l"
                        fmt = globals()[parts[0]]
                        print(fmt.format(macro, parts[1], second_arg))
                elif parts[1] == 'm':
                    fmt = globals()[parts[0] + '_m_x']
                    print(fmt.format(macro, parts[2]))
                elif parts[2] == 'm':
                    fmt = globals()[parts[0] + '_x_m']
                    print(fmt.format(macro, parts[1]))
        else:
            try:
                fmt = globals()[parts[0]]
            except KeyError:
                fmt = globals()["_" + parts[0]]
            if len(parts) == 1:
                print(fmt.format(macro))
            elif len(parts) == 2:
                second_arg = chr(ord(parts[1])+1) if parts[1] != "h" else "l"
                print(fmt.format(macro, parts[1], second_arg))
            else:
                print(fmt.format(macro, parts[1], parts[2]))
    print(default)
    print("}")
