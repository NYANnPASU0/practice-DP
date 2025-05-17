using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba2variant_Kapustina
{
    public class CoffeMachine
    {
        public int coffee = 10;
        public int milk = 10;
        public int chocolate = 10;
        public int RaspberrySyrup = 10;
        public int StrawberrySyrup = 10;
        public void CookLatte(ref int deposit)
        {
            if (coffee >= 1 && milk >= 6)
            {
                deposit -= 100;
                coffee -= 1;
                milk -= 6;
                if (RaspberrySyrup > 0 && StrawberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else if (RaspberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный - закончился");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый - закончился");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
            }
            else
            {
                if (coffee == 0 && milk < 6)
                {
                    Console.WriteLine("Недостаточно ингридиентов: кофе и молоко");
                }
                if (coffee == 0)
                {
                    Console.WriteLine("Недостаточно ингридиента: кофе");
                }
                else
                {
                    Console.WriteLine("Недостаточно ингридиета: молоко");
                }
                Console.WriteLine();
            }
        }
        public void CookCappuccino(ref int deposit)
        {
            if (coffee >= 1 && milk >= 4)
            {
                deposit -= 150;
                coffee -= 1;
                milk -= 4;
                if (RaspberrySyrup > 0 && StrawberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else if (RaspberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный - закончился");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый - закончился");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
            }
            else
            {
                if (coffee == 0 && milk < 4)
                {
                    Console.WriteLine("Недостаточно ингридиентов: кофе и молоко");
                }
                if (coffee == 0)
                {
                    Console.WriteLine("Недостаточно ингридиента: кофе");
                }
                else
                {
                    Console.WriteLine("Недостаточно ингридиета: молоко");
                }
                Console.WriteLine();
            }
        }
        public void CookEspresso(ref int deposit)
        {
            if (coffee >= 1 && milk >= 3)
            {
                deposit -= 200;
                coffee -= 1;
                milk -= 3;
                if (RaspberrySyrup > 0 && StrawberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else if (RaspberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный - закончился");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый - закончился");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
            }
            else
            {
                if (coffee == 0 && milk < 3)
                {
                    Console.WriteLine("Недостаточно ингридиентов: кофе и молоко");
                }
                else if (coffee == 0)
                {
                    Console.WriteLine("Недостаточно ингридиента: кофе");
                }
                else
                {
                    Console.WriteLine("Недостаточно ингридиета: молоко");
                }
                Console.WriteLine();

            }

        }
        public void CookClassicChocolate(ref int deposit)
        {
            if (chocolate >= 1 && milk >= 3)
            {
                deposit -= 150;
                chocolate -= 1;
                milk -= 3;
                if (RaspberrySyrup > 0 && StrawberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else if (RaspberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный - закончился");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый - закончился");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
            }
            else
            {
                if (chocolate == 0 && milk < 3)
                {
                    Console.WriteLine("Недостаточно ингридиентов: шоколад и молоко");
                }
                else if (chocolate == 0)
                {
                    Console.WriteLine("Недостаточно ингридиента: шоколад");
                }
                else
                {
                    Console.WriteLine("Недостаточно ингридиета: молоко");
                }
                Console.WriteLine();
            }
        }
        public void CookDoubleChocolate(ref int deposit)
        {
            if (chocolate >= 2 && milk >= 3)
            {
                deposit -= 200;
                chocolate -= 2;
                milk -= 3;
                if (RaspberrySyrup > 0 && StrawberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else if (RaspberrySyrup > 0)
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый");
                    Console.WriteLine("2. Клубничный - закончился");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 1:
                            Console.WriteLine("Добавление малинового сиропа");
                            RaspberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
                else
                {
                    Console.WriteLine("Добавить сиропы:");
                    Console.WriteLine("1. Малиновый - закончился");
                    Console.WriteLine("2. Клубничный");
                    Console.WriteLine("3. Без сиропа");
                    int tmp = Convert.ToInt32(Console.ReadLine());
                    switch (tmp)
                    {
                        case 2:
                            Console.WriteLine("Добавление клубничного сиропа");
                            StrawberrySyrup -= 1;
                            break;
                        default:
                            break;
                    }
                    Console.WriteLine();
                }
            }
            else
            {
                if (chocolate < 1 && milk < 3)
                {
                    Console.WriteLine("Недостаточно ингридиентов: шоколад и молоко");
                }
                else if (chocolate < 1)
                {
                    Console.WriteLine("Недостаточно ингридиента: шоколад");
                }
                else
                {
                    Console.WriteLine("Недостаточно ингридиета: молоко");
                }
                Console.WriteLine();
            }
        }
    }
}
