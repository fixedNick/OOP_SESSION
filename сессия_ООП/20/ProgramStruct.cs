// C# 9.0
using System;
using System.IO;

// Можно завернуть в namespace
Console.Write("Example 9.0"); // Точка входа

namepsace AnyNamespace
{
    class AnyClass
    {}
    struct AnyStruct
    {
    }
}

// C# < 9.0

using System;
using System.IO;

namespace ProgramName // AnyNamespaceName
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Example < C# 9.0"); // Точка входа
        }
    }
}