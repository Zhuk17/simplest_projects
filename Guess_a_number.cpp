#include <iostream>
#include <cstdlib> // для функций srand() и rand()
#include <ctime> // для функции time()
#include <cmath> // Для std::abs

// Генерируем случайное число между min и max.
// Предполагается, что srand() уже вызывали
int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    // Равномерно распределяем выбор случайного числа в диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Возвращаем true, если пользователь выиграл, false - если проиграл
bool playGame(int guesses, int number)
{
    int prevDiff = -1; // Предыдущая разница между числом и догадкой

    for (int count = 1; count <= guesses; ++count)
    {
        std::cout << "Попытка #" << count << ": ";
        int guess;
        std::cin >> guess;
        int diff = std::abs(number - guess);
        
        if (prevDiff != -1 && diff < prevDiff)
            std::cout << "Теплее\n";
        else if (prevDiff != -1 && diff > prevDiff)
            std::cout << "Холоднее\n";

        if (diff > 50)
            std::cout << "Очень холодно\n";
        else if (diff <= 25 && diff > 15)
            std::cout << "Холодно\n";
        else if (diff <= 15 && diff > 10)
            std::cout << "Прохладно\n";
        else if (diff <= 10 && diff > 5)
            std::cout << "Тепло\n";
        else if (diff <= 5)
            std::cout << "Очень горячо\n";
        else // догадка == число
            return true;

        prevDiff = diff;
    }

    return false;
}
 
bool playAgain()
{
    // Продолжаем спрашивать у пользователя, хочет ли он сыграть еще раз до тех пор, пока он не нажмет 'y' или 'n'
    char ch;
    do
    {
        std::cout << "Хотите ли сыграть сначала (y/n)? ";
        std::cin >> ch;
    } while (ch != 'y' && ch != 'n');
 
    return (ch == 'y');
}
 
int main()
{
    srand(static_cast<unsigned int>(time(0))); // в качестве стартового числа используем системные часы
    rand(); // сбрасываем первый результат
 
    const int guesses = 7; // у пользователя есть 7 попыток
 
    do 
    {
        int difficulty;
        int min = 1;
        int max;
        //
        std::cout << "Выберите уровень сложности от 1 до 3: " << std::endl;
        std::cin >> difficulty;
        if (difficulty == 1){
            max = 75;
        }
        else if (difficulty == 2){
            max = 100;
        }
        else if (difficulty == 3){
            max = 125;
        }
        else{
            std::cout << "Введите число от 1 до 3: " << std::endl;
        }

        int number = getRandomNumber(min, max); // число, которое пользователь должен угадать 
 
        std::cout << "Давай сыграем в игру, у вас есть " << guesses << " попыток отгадать число в интервале от 1 до " << max << "\n";
		
        bool won = playGame(guesses, number);
        if (won)
            std::cout << "Поздравляю, вы выиграли!\n";
        else
            std::cout << "К сожалению, вы проиграли. Загаднное число: " << number << "\n";
 
    }
    while (playAgain());
 
    std::cout << "Благодарим за игру\n";
    return 0;
}