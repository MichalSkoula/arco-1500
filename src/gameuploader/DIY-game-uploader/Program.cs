using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace DIY_game_uploader
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
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("DIY Arduino Handheld Game Console Uploading Software\n");

            COMPort comPorts = new COMPort();
            comPorts.printCOMPorts();
            int comPort = comPorts.selectCOMPort();

            Games games = new Games();
            games.printGames();
            string game = games.selectGame();

            Uploader uploader = new Uploader();
            uploader.upload(game, comPort);

            Console.ReadLine();
        }
    }
}
