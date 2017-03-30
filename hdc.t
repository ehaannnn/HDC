cup -2 main
calc: ssp 6
lda 4
ldc 5
ldc 4
mul
lod 3
ldc 3
div
ldc 2
lod 3
ldc 3
div
ldc 2
div
mul
sub
add
sto
lod 4
str 0
retf
main: ssp 13
lda 11
ldc 0
sto
for0: lod 11
ldc 10
les
fjp for1
lda 1
lod 11
add
mst
lod 11
cup 1 calc
sto
lda 11
lod 11
ldc 1
add
sto
ujp for0
for1: lda 12
ldc 0
sto
lda 13
lod 1
sto
lod 12
lod 13
les
fjp if0
lda 12
lod 13
sto
if0: lda 13
lod 2
sto
lod 12
lod 13
les
fjp if1
lda 12
lod 13
sto
if1: lda 13
lod 3
sto
lod 12
lod 13
les
fjp if2
lda 12
lod 13
sto
if2: lda 13
lod 4
sto
lod 12
lod 13
les
fjp if3
lda 12
lod 13
sto
if3: lda 13
lod 5
sto
lod 12
lod 13
les
fjp if4
lda 12
lod 13
sto
if4: lda 13
lod 6
sto
lod 12
lod 13
les
fjp if5
lda 12
lod 13
sto
if5: lda 13
lod 7
sto
lod 12
lod 13
les
fjp if6
lda 12
lod 13
sto
if6: lda 13
lod 8
sto
lod 12
lod 13
les
fjp if7
lda 12
lod 13
sto
if7: lda 13
lod 9
sto
lod 12
lod 13
les
fjp if8
lda 12
lod 13
sto
if8: lda 13
lod 10
sto
lod 12
lod 13
les
fjp if9
lda 12
lod 13
sto
if9: lod 12
out
stp
