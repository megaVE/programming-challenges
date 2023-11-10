from random import randint

n = randint(20, 30)
while True:
    print(f'{n:2}', '|' * n)
    v = int(input('Your turn: '))
    if not 1 <= v <= min(3, n):
        continue
    
    n -= v
    if n == 0:
        print('You win')
        break
    
    print(f'{n:2}', '|' * n)
    v = n % 4 or randint(1, min(3, n))
    print('Bot turn:', v)
    n -= v
    if n == 0:
        print('You lose')
        break