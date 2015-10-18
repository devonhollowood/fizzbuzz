layout:
aaaabbbbcdefghhhhh
a = fizz string
b = buzz string
c = newline
d = main counter (counts down from 100)
e = fizz counter (counts down from 3 repeatedly)
f = buzz counter (counts down form 5 repeatedly)
g = fizzbuzz flag (set if this number has been fizzed or buzzed)
h = number printing workspace

write fizzbuzz\n string (touches next space but then sets to zero)
>>>>> >>>> go to space after string
+++++ +++++ loop 10x
[ <<<<< <<<< go to start
+++++ ++   > F = 70
+++++ ++   > I = 73
+++++ ++++ > Z = 90
+++++ ++++ > Z = 90
+++++ ++   > B = 66
+++++ +++  > U = 85
+++++ ++++ > Z = 90
+++++ ++++ > Z = 90
+          > newline = 10
- decrement loop counter
]
<<<<< <<< go to I (F already okay)
+++   > fix I
      > Z okay
      > Z okay
----  > fix B
+++++ > fix U
      > Z okay
      > Z okay
      > newline okay
end at main counter

set main counter to 100 (touches next space but then sets to zero)
> +++++ +++++ [ < +++++ +++++ > - ]
ends at fizz counter

set fizz counter to 3
+++
> go to buzz counter

set buzz counter to 5
+++++
<< go to main counter

[ main loop (lasts until main counter is zero)

- decrement main counter

> go to fizz counter
- decrement fizz counter

if fizz counter zero print "fizz"
[ - >>> + > + <<<< ] >>>> [ - <<<< + >>>> ] copy fizz counter to h0 (end at h1)
+ < [ [-] > - < ] > set flag at h1 if h0 (copied fizz counter) is zero
[ - if (h1 is nonzero; ie h0 is zero; ie fizzing)
<< + set fizzbuzz flag
<<<<< <<<<< << go to "fizz"
. > . > . > . print fizz
>>>>> >> +++ go to fizz counter and restock
>>>> return to h1
] end of "fizzing" loop

<<< go to buzz counter
- decrement buzz counter

[ - >> + > + <<< ] >>> [ - <<< + >>> ] copy buzz counter to h0 (end at h1)
+ < [ [-] > - < ] > set flag at h1 if h0 (copied buzz counter) is zero
[ - if (h1 is nonzero; ie h0 is zero; ie buzzing)
<< + set fizzbuzz flag
<<<<< <<< go to "buzz"
. > . > . > . print buzz
>>>> +++++ go to buzz counter and restock
>>> return to h1
] end of "buzzing" loop

< go to h0 (one after fizzbuzz flag)
+ < [ [-] > - < ] > set flag at h0 if fizzbuzz flag nonzero

[ - if (h0 is nonzero; ie fizzbuzz flag not set; ie normal number)

set h0 to the number we want to print (namely 100 minus main counter):
<<<< go to main counter
copy main counter to h1 (end at h0)
[ - >>>> + > + <<<<< ] >>>> [ - <<<< + >>>> ]
>> +++++ +++++ [ - << +++++ +++++ >> ] set h0 = 100 (end at h2)
< [ - < - > ] set h0 = 100 minus h1 = 100 minus main counter
end at h1

move main counter into digits
each digit is initially stored as 10 minus that digit
set up digit registers at h1 to h3 (h1 is hundreds; h3 is ones)
+++++ +++++ > +++++ +++++ > +++++ +++++ initialize digits
<<< go back to copied main counter (h0)
[ - decrement h0
>>> - go to ones digit and decrement
[ - > + > + << ] >> [ - << + >> ] copy ones digit into h4
+ < [ [-] > - < ] > [ - if ones digit is zero
<<< - > +++++ +++++ decrement tens and restock ones
< go to tens digit
[ - >> + > + <<< ] >>> [ - <<< + >>> ] copy tens digit into h4
if tens digit is zero decrement hundreds and restock tens
+ < [ [-] > - < ] > [ - <<<< - > +++++ +++++ >>> ]
]
<<<<< go back to h0
]

subtract each digit from ten
+++++ +++++ make ten
> go to hundreds
[ - < - > ] subtract from ten
< [ - > + < ] copy over remainder
+++++ +++++ make ten
>> go to tens
[ - << - >> ] subtract from ten
<< [ - >> + << ] copy over remainder
+++++ +++++ make ten
>>> go to ones
[ - <<< - >>> ] subtract from ten
<<< [ - >>> + <<< ] copy over remainder
end at h0

print digits
>>>>> go to h4
+++++ +++ [ < +++++ + > - ] < set h4 to 8x6 = 48 = '0'
[ <<< + > + > + > - ] add this '0' to back digits
<<< .[-] > .[-] > .[-] print digits then set them to zero

<<< go back to h0 (where fizzbuzz flag loop started)

] end of "fizzbuzz flag not set" loop

<<<<<. go to newline and print

>return to main counter

] end of main loop
