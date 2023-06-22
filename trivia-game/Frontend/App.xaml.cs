using System.Windows;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public static string? username;

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