Стандартна бібліотека вводу-виводу в C++ надає кілька функцій для роботи з введенням та виведенням даних, головними серед яких є std::cin, std::cout та std::cerr. Їх ефективність та швидкість виконання можуть значно відрізнятися залежно від використання буферизації та розміру буфера.
Буферизовані функції: за замовчуванням, стандартні потоки вводу-виводу в C++ (std::cin, std::cout) є буферизованими. Це означає, що дані спочатку записуються у внутрішній буфер, і лише після його заповнення або виклику функції flush (std::cout << std::flush) буфер виводиться на екран або записується у файл. Це дозволяє значно зменшити кількість викликів до системних функцій введення-виведення, що часто є дуже повільними.
Небуферизовані функції: std::cerr за замовчуванням є небуферизованим, тобто дані записуються на екран або у файл негайно після їх подання у потік. Це забезпечує негайний вивід помилок або діагностичних повідомлень, але може уповільнювати роботу через часті виклики системних функцій.
Буферизований режим з малим буфером: при використанні маленького буфера програма працюватиме швидше, ніж у небуферизованому режимі, але повільніше, ніж при використанні великого буфера.
Буферизований режим з великим буфером: зі збільшенням розміру буфера час виконання значно скорочується, оскільки кількість викликів до системних функцій зменшується.
Небуферизований режим: у небуферизованому режимі час виконання буде найтривалішим через часті виклики системних функцій для кожного запису.


Ofstream buffered output with buffer size 1024 took 0.608449 seconds on average
Ofstream buffered output with buffer size 2048 took 0.405528 seconds on average
Ofstream buffered output with buffer size 4096 took 0.369578 seconds on average
Ofstream buffered output with buffer size 8192 took 0.320746 seconds on average
Ofstream unbuffered output took 9.79931 seconds on average
Std::cout buffered output with buffer size 1024 took 11.768 seconds on average
Std::cout buffered output with buffer size 2048 took 11.1346 seconds on average
Std::cout buffered output with buffer size 4096 took 10.7784 seconds on average
Std::cout buffered output with buffer size 8192 took 10.7625 seconds on average
Std::cout unbuffered output took 39.1069 seconds on average
Printf buffered output with buffer size 1024 took 12.7909 seconds on average
Printf buffered output with buffer size 2048 took 12.1251 seconds on average
Printf buffered output with buffer size 4096 took 11.8206 seconds on average
Printf buffered output with buffer size 8192 took 12.4653 seconds on average
Printf unbuffered output took 561.031 seconds on average
Fprintf buffered output with buffer size 1024 took 1.46825 seconds on average
Fprintf buffered output with buffer size 2048 took 1.37499 seconds on average
Fprintf buffered output with buffer size 4096 took 1.30601 seconds on average
Fprintf buffered output with buffer size 8192 took 1.29869 seconds on average
Fprintf unbuffered output took 166.605 seconds on average



1024
2048
4096
8192
0


| Column 1 | Column 2 | Column 3 |
|----------|----------|----------|
| Row 1    | Cell 2   | Cell 3   |
| Row 2    | Cell 5   | Cell 6   |
| Row 3    | Cell 8   | Cell 9   |

|          | 1КБ      | 2КБ      | 4КБ      | 8КБ      | 16КБ | Unbuffered |
|----------|----------|----------|----------|----------|------|------------|
| Ofstream | 0.608449 | 0.405528 | 0.369578 | 0.320746 |      | 9.79931    |
| cout     | 11.768   | 11.1346  | 10.7784  | 10.7625  |      | 39.1069    |
| Printf   | 12.7909  | 12.1251  | 11.8206  | 12.4653  |      | 561.031    |
| Fprintf  | 1.46825  | 1.37499  | 1.30601  | 1.29869  |      | 166.605    |

