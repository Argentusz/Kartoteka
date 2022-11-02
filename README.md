# Kartoteka

*Kartoteka is a C project made within a framework of a course project by Maksim Trostin*

## Original Task

Create a card-index stored on a disk and a program that interacts with it

Program should be able to do the folowing:
- Adding data to card-index
- Changing data (deleting, correcting, adding)
- Finding data by any attribute
- Sorting data by any attribute
- Output results on a screen and saving it in a file

Requirements to the program:
- **Structured programming paradigm**
- User-freindly interface
- Menu for choosing modes of opernations
- Accounting peculiarities of different OS
- All the variables defined before first operator
- Initialisation while defining only for pointers (into NULL)
- **Strict C90**

> Создать электронную картотеку, хранящуюся на диске, и программу, обеспечивающую взаимодействие с ней.  
> Программа должна выполнять следующие действия:
> - занесение данных в электронную картотеку;
> - внесение изменений (исключение, корректировка, добавление);
> - поиск данных по различным признакам;
> - сортировку по различным признакам;
> - вывод результатов на экран и сохранение на диске.
> 
> Требования к реализации программы  
>> - Парадигма - структурная  
> - Дружелюбный интерфейс (диалог с пользователем)
> - Меню для выбора вариантов работы
> - Очистка экрана после завершения каждого варианта работы
> - Учет особенностей различных операционных систем
> - Все переменные должны быть описаны до первого оператора в функции
> - Инициализация при описании допускается только для указателей (начальная установка в NULL).
> - Должны соблюдаться соглашения strict C90 !!
## Functions Documentation
### General
- Functions can contain parameters that can be printed by a user with a function (in documentation parameters appear in <_>)  
  *Without parameters Function will be asked for them afterwards (except `Show` Function)*
- Deifferent Functions can be called in one line using `&` sign *(e.g. Swap 1 2 & Show 3)*
- Kartoteka uses `kartoteka.csv` file to save information *(see `Save` and `Help` Functions)*
  At the start of the program uses it to load information
### Quit
Quits the program.
### Save
Saves data into save file `kartoteka.csv`  
At the next start of the program Kartoteka will use this file to load data
### Enter <_csv/lbl_>
Allows to enter a new lines into card-index.  
Has two modes: CSV and Line-By-Line.  
First allows you to enter lines in CSV format until "Stop" string is entered.

Usage Example:
```
>>> Enter csv
one;two;3;4;5;6;7;8;9
another;one;3;4;5;6;7;8;9
Stop
```

Second one allows you to enter lines "Line by Line"

Usage Example:
```
>>> Enter lbl
Enter the name: one
Enter the faculty: two
Enter the Age: 3
Enter the ID: 4
Enter the Average Score: 5
Enter the Completion Rate: 6
Enter the GIA Result #1: 7
Enter the GIA Result #2: 8
Enter the GIA Result #3: 9
Would you like to Enter Line by line once more? (Y/N): N
```
### Import <_filename_>
Imports CSV file with a given name and adds data into program

Usage Examples:
```
>>> Import file.csv
Done.
```
```
>>> Import
Type File Name to import from (Just hit Enter to cancel): file.csv
Done.
```
### Export <_filename_>
Exports data into a CSV file that can be later imported

Usage Example:
```
>>> Export out
warning: File 'out' already exists.
This will overwrite the file
Are you sure you want to continue? (Y/N): Y
Done.
```
### Show <_maxamount_>
Shows up to max amount of lines.   
*Unlike the other functions parameter is unnecessary.  
If parameter is not given Show Function will show all the lines.*

Usage Examples:
```
>>> Show 5
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 1  | Woland W.               | FKTI    | 999 | 5.000 | 1.00 | 100 | 100 | 100 |
| 2  | 2  | Smirnov S.M.            | FEI     | 20  | 4.900 | 0.90 | 90  | 90  | 86  |
| 3  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
--------------------------------------------------------------------------------------
| Hidden : 2                                                                         |
```
```
>>> Show
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 1  | Woland W.               | FKTI    | 999 | 5.000 | 1.00 | 100 | 100 | 100 |
| 2  | 2  | Smirnov S.M.            | FEI     | 20  | 4.900 | 0.90 | 90  | 90  | 86  |
| 3  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
| 6  | 6  | Ivanov I.I.             | FKTI    | 18  | 3.281 | 0.54 | 85  | 90  | 92  |
| 7  | 7  | Duda A.                 | FRT     | 19  | 3.900 | 0.96 | 89  | 90  | 91  |
```
### Change <_No_> <_csv/lbl_>
Changes line with a given No.  
Has two modes: CSV and Line-By-Line (just like `Enter` Function)

Usage Example:
```
>>> Change 2 csv
Enter One CSV Kartoteka line.
one;two;3;4;5;6;7;8;9
Done.
```
### Swap <_No1_> <_No2_>
Swaps two lines with a given No\`s

Usage Example:
```
>>> Swap 1 2
Done.
```
### Sort <_Column_> <_a/d_>
Sorts data by a given *Column* in *ascending/descending* order

Available Columns:  
- Name
- Faculty
- Age
- ID
- Score
- CR
- GIA 1
- GIA 2
- GIA 3

Usage Example:
```
>>> Sort Name a
Done.
```
### Filter <_Column_> <_(how)value_>
Shows all the lines that satisfy requirements

Available Columns:  
- Name
- Faculty
- Age
- ID
- Score
- CR
- GIA 1
- GIA 2
- GIA 3

Available Requirements:
- \> (more)
- < (less)
- \>= (more or equal)
- <= (less or equal)
- == (strict equal)
- = (non-strict equal)

*Note: non-strict equal (=) will consider **string** value as a first substring  
       strict equal (==) will look for exact match.  
       These two signs will behave equally for numerous columns*

Usage Examples:
```
>>> Filter ID >= 5
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 1  | 7  | Duda A.                 | FRT     | 19  | 3.900 | 0.96 | 89  | 90  | 91  |
| 2  | 6  | Ivanov I.I.             | FKTI    | 18  | 3.281 | 0.54 | 85  | 90  | 92  |
| 3  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
```
```
>>> Filter Name = Smirnov
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 3  | 5  | Smirnov A.A.            | FKTI    | 17  | 2.500 | 0.09 | 75  | 60  | 99  |
| 4  | 4  | Smirnov A.A.            | FEI     | 18  | 4.228 | 0.67 | 70  | 70  | 70  |
| 5  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
```
```
>>> Filter Name == Smirnov S.S.
| No | ID | Name                    | Faculty | Age | Score | C.R. | GIA Results     |
| 5  | 3  | Smirnov S.S.            | FEI     | 18  | 4.050 | 0.87 | 86  | 86  | 87  |
```
### Delete All
Delets all the data
### Delete <_No_>
Deletes line with a give No

Usage Example:
```
>>> Delete 2
Done.
```
### Delete By <_Column_> <_(how)value_>
Deletes all the lines that satisfy requirements (similiar to `Filter` Function)

Available Columns:  
- Name
- Faculty
- Age
- ID
- Score
- CR
- GIA 1
- GIA 2
- GIA 3

Available Requirements:
- \> (more)
- < (less)
- \>= (more or equal)
- <= (less or equal)
- == (strict equal)
- = (non-strict equal)

*Note: non-strict equal (=) will consider **string** value as a first substring  
       strict equal (==) will look for exact match.  
       These two signs will behave equally for numerous columns*

Usage Examples:
```
>>> Delete By Age > 18
Done.
```
```
>>> Delete By Name = Brzeczyszczykiewicz
Done.
```
```
>>> Delete By Name == Brzeczyszczykiewicz G.
Done.
```
### Quick
Shows first 5 lines of database.  
*Called at the first launch of the program*
### Source
Shows a link to this GitHub repository 
### Help <_Command_>
If not given any argument shows list of all available commands  
Else shows specific Function documentation

Usage Examples:
```
>>> Help
Available Commands:
Quit                             - to quit
Save                             - to save data into save file
Enter <csv/lbl>                  - to fill Kartoteka from keyboard
Import <file name>               - to fill Kartoteka from file
Export <file name>               - to make file from Kartoteka data
Show <max amount>                - to show up to positive max amount of lines
Change <No> <csv/lbl>            - to change line #N from keyboard
Swap <No1> <No2>                 - to swap lines with no N1 and N2
Sort <Column> <a/d>              - to sort column ascending/descending
Filter <Column> <(how)value>     - to show all lines with necessary value
Delete All                       - to delete all Kartoteka database
Delete <No>                      - to delete line #N
Delete By <Column> <(how)value>  - to delete lines with necessary value
Quick                            - to quick look data in Kartoteka
Clear                            - to clear the screen
<Command> & <Command> . . .      - to deploy several Commands
Source                           - to show a link on a source code.
Help <Command>                   - for documentation

Use Help <Command> for specific Function documentation
```
```
>>> Help Help
Help function is used to keep documentation
And access it from the program
With no arguments shows all the available Kartoteka commands
Can also show documentation of the specific function

Usage Example:
Help Enter
```
## Within Source Code
- Defined *boolean* type as a char that keeps only 0 or 1 for easier code reading *(since C90 has no __bool__ type)*
- Internal functions named with an underscore line at the end *(except BFuncs functions that were written by me before this project)*
