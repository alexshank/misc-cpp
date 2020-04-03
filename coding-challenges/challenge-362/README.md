# [2018-05-30] Challenge #362 [Intermediate] "Route" Transposition Cipher
From https://www.reddit.com/r/dailyprogrammer/comments/8n8tog/20180530_challenge_362_intermediate_route/

<i>Uses C++11 functions, so compile accordingly.</i>

### <b>Description</b>
You've been taking some classes at a local university. Unfortunately, your theory-of-under-water-basket-weaving professor is really boring. He's also very nosy. In order to pass the time during class, you like sharing notes with your best friend sitting across the aisle. Just in case your professor intercepts any of your notes, you've decided to encrypt them.

To make things easier for yourself, you're going to write a program which will encrypt the notes for you. You've decided a transposition cipher is probably the best suited method for your purposes.

A transposition cipher is "a method of encryption by which the positions held by units of plaintext (which are commonly characters or groups of characters) are shifted according to a regular system, so that the ciphertext constitutes a permutation of the plaintext" (En.wikipedia.org, 2018).

Specifically, we will be implementing a type of route cipher today. In a route cipher the text you want to encrypt is written out in a grid, and then arranged in a given pattern. The pattern can be as simple or complex as you'd like to make it.

### <b>Task</b>
For our purposes today, your program should be able to accommodate two input paramters: Grid Dimensions, and Clockwise or Counterclockwise Rotation. To make things easier, your program need only support the Spiral route from outside to inside.

### <b>Example</b>
Take the following message as an example:

```
WE ARE DISCOVERED. FLEE AT ONCE
```

Given inputs may include punctuation, however the encrypted text should not. Further, given text may be in all caps, all lower case, or a mix of the two. The encrypted text must be in all caps.

You will be given dimensions in which to write out the letters in a grid. For example dimensions of:

9, 3

Would result in 9 columns and 3 rows:

```
W   E   A   R   E   D   I   S   C
O   V   E   R   E   D   F   L   E
E   A   T   O   N   C   E   X   X
```

As you can see, all punctuation and spaces have been stripped from the message.

For our cipher, text should be entered into the grid left to right, as seen above.

Encryption begins at the top right. Your route cipher must support a Spiral route around the grid from outside to the inside in either a clockwise or counterclockwise direction.

For example, input parameters of clockwise and (9, 3) would result in the following encrypted output:

```
C   E   X   X   E   C   N   O   T
A   E   O   W   E   A   R   E   D
I   S   L   F   D   E   R   E   V
```

Beginning with the C at the top right of the grid, you spiral clockwise along the outside, so the next letter is E, then X, and so on eventually yielding the output above.

### <b>Input Description</b>
Input will be organized as follows:

"string" (columns, rows) rotation-direction

<b>Note:</b> If the string does not fill in the rectangle of given dimensions perfectly, fill in empty spaces with an X.

So,

```
"This is an example" (6, 3) clockwise
```

becomes

```
T   H   I   S   I   S
A   N   E   X   A   M
P   L   E   X   X   X
```

### <b>Challenge Inputs</b>
```
"WE ARE DISCOVERED. FLEE AT ONCE" (9, 3) clockwise
"why is this professor so boring omg" (6, 5) counter-clockwise
"Solving challenges on r/dailyprogrammer is so much fun!!" (8, 6) counter-clockwise
"For lunch let's have peanut-butter and bologna sandwiches" (4, 12) clockwise
"I've even witnessed a grown man satisfy a camel" (9,5) clockwise
"Why does it say paper jam when there is no paper jam?" (3, 14) counter-clockwise
```

### <b>Challenge Outputs</b>
```
"CEXXECNOTAEOWEAREDISLFDEREV"
"TSIYHWHFSNGOMGXIRORPSIEOBOROSS"
"CGNIVLOSHSYMUCHFUNXXMMLEGNELLAOPERISSOAIADRNROGR"
"LHSENURBGAISEHCNNOATUPHLUFORCTVABEDOSWDALNTTEAEN"
"IGAMXXXXXXXLETRTIVEEVENWASACAYFSIONESSEDNAMNW"
"YHWDSSPEAHTRSPEAMXJPOIENWJPYTEOIAARMEHENAR"
```

### <b>Bonus</b>
A bonus solution will support at least basic decryption as well as encryption.

### <b>Bonus 2</b>
Allow for different start positions and/or different routes (spiraling inside-out, zig-zag, etc.), or for entering text by a different pattern, such as top-to-bottom.

### <b>References</b>
En.wikipedia.org. (2018). Transposition cipher. Available at: https://en.wikipedia.org/wiki/Transposition_cipher [Accessed 12 Feb. 2018].

### <b>Credit</b>
This challenge was posted by user /u/FunWithCthulhu3, many thanks. If you have a challenge idea, please share it in /r/dailyprogrammer_ideas and there's a good chance we'll use it.
