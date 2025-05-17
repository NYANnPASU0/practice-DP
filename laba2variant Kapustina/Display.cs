using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba2variant_Kapustina
{
    public class Display
    {
        public int state;
        public int _deposit = 0;
        public void display(CoffeMachine machine, Management manage)
        {
            while (true)
            {
                if (_deposit == 0)
                {
                    Console.WriteLine("Внесите депозит");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    Console.WriteLine();
                    _deposit += tmp;
                }
                else
                {
                    Console.WriteLine("Текущий баланс: " + _deposit);
                    Console.WriteLine("Выберите, что приготовить:");
                    Console.WriteLine("1. Латте - 100 рублей");
                    Console.WriteLine("2. Капучино - 120 рублей");
                    Console.WriteLine("3. Эспрессо - 150 рублей");
                    Console.WriteLine("4. Горячий шоколад - 150 рублей");
                    Console.WriteLine("5. Двойной горячий шоколад - 180 рублей");
                    Console.WriteLine("6. Пополнить депозит");
                    Console.WriteLine("7. Выход");
                    state = Convert.ToInt32(Console.ReadLine());
                    switch (state)
                    {
                        case 1:
                            if (_deposit < 100)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("Недостаточно средств");
                                Console.WriteLine();
                                Console.ResetColor();
                            }
                            else
                            {
                                Console.ForegroundColor = ConsoleColor.Blue;
                                Console.WriteLine("Добавление растворимого кофе");
                                Console.WriteLine("Добавление воды");
                                Console.WriteLine("Добавление сухого молока");
                                Console.WriteLine("Добавление воды");
                                Console.WriteLine("Добавление сахара");
                                Console.WriteLine("Подача напитка");
                                Console.WriteLine();
                                Console.ResetColor();
                                CookLatte cook = new CookLatte(machine);
                                manage.SetCommand(cook);
                                manage.PressButton(ref _deposit);
                            }
                            break;
                        case 2:
                            if (_deposit < 120)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("Недостаточно средств");
                                Console.WriteLine();
                                Console.ResetColor();
                            }
                            else
                            {
                                Console.ForegroundColor = ConsoleColor.Blue;
                                Console.WriteLine("Добавление растворимого кофе");
                                Console.WriteLine("Взбивание молока");
                                Console.WriteLine("Наливается эспрессо");
                                Console.WriteLine("Добавление молочной пены");
                                Console.WriteLine("Подача напитка");
                                Console.WriteLine();
                                Console.ResetColor();
                                CookCappuccino cook = new CookCappuccino(machine);
                                manage.SetCommand(cook);
                                manage.PressButton(ref _deposit);
                            }
                            break;
                        case 3:
                            if (_deposit < 150)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("Недостаточно средств");
                                Console.WriteLine();
                                Console.ResetColor();
                            }
                            else
                            {
                                Console.ForegroundColor = ConsoleColor.Blue;
                                Console.WriteLine("Помол кофе");
                                Console.WriteLine("Прогрев воды");
                                Console.WriteLine("Пролив воды через кофе");
                                Console.WriteLine("Подача напитка");
                                Console.WriteLine();
                                Console.ResetColor();
                                CookEspresso cook = new CookEspresso(machine);
                                manage.SetCommand(cook);
                                manage.PressButton(ref _deposit);
                            }
                            break;
                        case 4:
                            if (_deposit < 150)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("Недостаточно средств");
                                Console.WriteLine();
                                Console.ResetColor();
                            }
                            else
                            {
                                Console.ForegroundColor = ConsoleColor.Blue;
                                Console.WriteLine("Нагрев молока");
                                Console.WriteLine("Добавление шоколада");
                                Console.WriteLine("Перемешивание");
                                Console.WriteLine("Подача напитка");
                                Console.WriteLine();
                                Console.ResetColor();
                                CookClassicChocolate cook = new CookClassicChocolate(machine);
                                manage.SetCommand(cook);
                                manage.PressButton(ref _deposit);
                            }
                            break;
                        case 5:
                            if (_deposit < 180)
                            {
                                Console.ForegroundColor = ConsoleColor.Red;
                                Console.WriteLine("Недостаточно средств");
                                Console.WriteLine();
                                Console.ResetColor();
                            }
                            else
                            {
                                Console.ForegroundColor = ConsoleColor.Blue;
                                Console.WriteLine("Нагрев молока");
                                Console.WriteLine("Добавление двойной порции шоколада");
                                Console.WriteLine("Интенсивное перемешивание ");
                                Console.WriteLine("Подача напитка");
                                Console.WriteLine();
                                Console.ResetColor();
                                CookDoubleChocolate cook = new CookDoubleChocolate(machine);
                                manage.SetCommand(cook);
                                manage.PressButton(ref _deposit);
                            }
                            break;
                        case 6:
                            Console.ForegroundColor = ConsoleColor.Cyan;
                            Console.WriteLine("Внесите депозит");
                            int tmp = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine();
                            Console.ResetColor();
                            _deposit += tmp;
                            break;
                        case 7:
                            Console.WriteLine("Выход из системы");
                            Console.WriteLine();
                            return;
                        default:
                            Console.WriteLine("Неверно выбранная операция");
                            Console.WriteLine();
                            break;
                    }
                }
            }
        }
    }
}
