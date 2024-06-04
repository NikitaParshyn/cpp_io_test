Програма тестує функції ofstream, cout, printf, fprintf на швидкість роботи з буфером та без. Для цього вона підраховує скільки часу займає вивід мільйону рядків з буфером із різним буфером (1Кб, 2Кб, 4Кб, 8Кб , 16Кб) розмір яких записується у файлі "buffer_sizes.dat" та підраховує скільки часу займає виконання того ж самого без буферу. Така перевірка проводиться 5 разів, а після виводяться серднє статистичне з цих результатів у файл "results.txt".  

**Результати виконання тесту:**  

Ofstream buffered output with buffer size 1024 took 0.608449 seconds on average  
Ofstream buffered output with buffer size 2048 took 0.405528 seconds on average  
Ofstream buffered output with buffer size 4096 took 0.369578 seconds on average  
Ofstream buffered output with buffer size 8192 took 0.320746 seconds on average  
Ofstream buffered output with buffer size 16384 took 0.303477 seconds on average  
Ofstream unbuffered output took 9.79931 seconds on average  
Std::cout buffered output with buffer size 1024 took 11.768 seconds on average  
Std::cout buffered output with buffer size 2048 took 11.1346 seconds on average  
Std::cout buffered output with buffer size 4096 took 10.7784 seconds on average  
Std::cout buffered output with buffer size 8192 took 10.7625 seconds on average  
Std::cout buffered output with buffer size 16384 took 10.4052 seconds on average  
Std::cout unbuffered output took 39.1069 seconds on average  
Printf buffered output with buffer size 1024 took 12.7909 seconds on average  
Printf buffered output with buffer size 2048 took 12.1251 seconds on average  
Printf buffered output with buffer size 4096 took 11.8206 seconds on average  
Printf buffered output with buffer size 8192 took 12.4653 seconds on average  
Printf buffered output with buffer size 16384 took 12.3917 seconds on average  
Printf unbuffered output took 561.031 seconds on average  
Fprintf buffered output with buffer size 1024 took 1.46825 seconds on average  
Fprintf buffered output with buffer size 2048 took 1.37499 seconds on average  
Fprintf buffered output with buffer size 4096 took 1.30601 seconds on average  
Fprintf buffered output with buffer size 8192 took 1.29869 seconds on average  
Fprintf buffered output with buffer size 16384 took 1.12878 seconds on average  
Fprintf unbuffered output took 166.605 seconds on average  

Таким чином можна зробити таблицю з отриманих даних:  

|          | 1КБ       | 2КБ       | 4КБ       | 8КБ       | 16КБ      | Unbuffered  |
|----------|-----------|-----------|-----------|-----------|-----------|-------------|
| Ofstream | 0.608449s | 0.405528s | 0.369578s | 0.320746s | 0.303477s | 9.79931s    |
| cout     | 11.768s   | 11.1346s  | 10.7784s  | 10.7625s  | 10.4052s  | 39.1069s    |
| Printf   | 12.7909s  | 12.1251s  | 11.8206s  | 12.4653s  | 12.3917s  | 561.031s    |
| Fprintf  | 1.46825s  | 1.37499s  | 1.30601s  | 1.29869s  | 1.12878s  | 166.605s    |

Таким чином можна зробити висновки що при виводі великої кількості даних краще використовувавти функцію Ofstream з буфером, а найгірше Printf. Також при виконанні тестів можна помітити закономірність, що функції, які виводять повідомлення у консоль виконуються у рази довше ніж функції, які виводять дані у файл, тож при виводі великої кількості даних краще виводи їх у файл. 

