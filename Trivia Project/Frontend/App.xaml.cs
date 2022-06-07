using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private App()
        {
            Communicator.Init("127.0.0.1", 4206);
        }
        private void ExitApp(object sender, ExitEventArgs e)
        {
            Communicator.Send(Communicator.RequestType.LogoutRequest, "");
        }
        

    }
}