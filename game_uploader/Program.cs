using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;

namespace ARCO1500_Uploader
{
    class Program
    {
        #if DEBUG
            public static bool debug = true;
        #else
            public static bool debug = false;
        #endif

        static void Main(string[] args)
        {
            
            Console.SetWindowSize(80, 40);
            Console.SetBufferSize(80, 40);
            Console.Beep(1500, 500);

            // print nice ASCI logo
            string title = @"
           _____   _____ ____    _ ___  __   __  
     /\   |  __ \ / ____/ __ \  / | __|/  \ /  \ 
    /  \  | |__) | |   | |  | | | |__ \ () | () |
   / /\ \ |  _  /| |   | |  | | |_|___/\__/ \__/ 
  / ____ \| | \ \| |___| |__| |                  
 /_/    \_\_|  \_\\_____\____/
";
            //Console.WriteLine(title);

            int i = 0;
            foreach (char l in title)
            {
                if (i <= 32)
                {
                    Console.ForegroundColor = ConsoleColor.Cyan;
                } else
                {
                    Console.ForegroundColor = ConsoleColor.Magenta;
                }
                Console.Write(l);
                Thread.Sleep(2);  

                i++;
                if (i > 50)
                {
                    i = 0;
                }
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine(" __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ __ ");
            Console.WriteLine();

            // COM ports
            COMPort comPorts = new COMPort();
            comPorts.printCOMPorts();
            int comPort = comPorts.selectCOMPort();

            // Games
            Games games = new Games();
            bool isFolderOk = games.printGames();
            if (!isFolderOk)
            {
                return;
            }
            string game = games.selectGame();

            // Upload
            Uploader uploader = new Uploader();
            uploader.upload(game, comPort);

            Console.ReadLine();
        }
    }
}
