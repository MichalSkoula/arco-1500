using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Management;

namespace DIY_game_uploader
{
    class Driver
    {
        public bool CheckDriver()
        {
            Console.WriteLine("Checking USB driver");
            SelectQuery query = new SelectQuery("Win32_SystemDriver");
            query.Condition = "Name like '%CH341%'";
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);
            if(searcher.Get().Count > 0)
            {
                Console.WriteLine("USB driver already installed\n");
                return true;
            }
            else
            {
                Console.WriteLine("USB driver not found. Please, install it first - arduino\\drivers\\CH341SER\\SETUP.EXE\n");
                Console.ReadKey();
                Environment.Exit(1);
                return false;
            }
        }
    }
}
