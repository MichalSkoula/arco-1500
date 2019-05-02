using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace DIY_game_uploader
{
    class Games
    {
        private string gamesFolder;
        private int gameNumber;
        private string[] availableGames;

        public bool printGames()
        {
            gamesFolder = getGamesFolder();
            if (gamesFolder == "")
            {
                Console.WriteLine("Game folder not found");
                Console.Beep(500, 3000);
                return false;
            }

            // get available games
            Console.WriteLine("\nAvailable games:");

            availableGames = Directory.GetDirectories(gamesFolder);
            int i = 0;
            string gameTitle;
            foreach (string s in availableGames)
            {
                gameTitle = s.Substring(s.IndexOf("games"));
                Console.WriteLine(i + ": " + gameTitle);
                i++;
            }

            return true;
        }

        public string selectGame()
        {
            // let user choose game
            do
            {
                Console.WriteLine("\nInsert game number and press ENTER");
                string gameNumberRead = Console.ReadLine();
                if (!Regex.IsMatch(gameNumberRead, @"^\d+$"))
                {
                    gameNumber = -1;
                }
                else
                {
                    gameNumber = int.Parse(gameNumberRead);
                }
            } while (availableGames.ElementAtOrDefault(gameNumber) == null);

            return availableGames[gameNumber];
        }

        private string getGamesFolder()
        {
            // get folder with games
            string gamesFolder = Program.debug ? "..\\..\\..\\..\\games" : "..\\games";
            if (!Directory.Exists(gamesFolder))
            {
                // not found...exit
                return "";
            }

            return gamesFolder;
        }
    }
}
