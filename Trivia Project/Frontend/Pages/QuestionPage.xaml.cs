
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Frontend.Requests;
using Frontend.Responses;
using Newtonsoft.Json;
using System.ComponentModel;
using Frontend.Pages;
using System.Windows.Threading;

namespace Frontend
{
    /// <summary>
    /// Interaction logic for QuestionPage.xaml
    /// </summary>
    public partial class QuestionPage : Page
    {
        private Button[] buttons;
        private int selectedButtonIndex = 4;
        BackgroundWorker serverListener = new BackgroundWorker();
        DispatcherTimer answerTime = new DispatcherTimer();

        private void initializeTimer()
        {
            answerTime.Interval = TimeSpan.FromSeconds(1);
            answerTime.Tick += (sender, args) =>
            {
                int minutesLeft = int.Parse(timeLBL.Content.ToString().Split(':')[0]);
                int secondsLeft = int.Parse(timeLBL.Content.ToString().Split(':')[1]);
                int totalSecondsLeft = minutesLeft * 60 + secondsLeft;

                totalSecondsLeft -= 1; //Tick
                timeLBL.Content = "0" + totalSecondsLeft / 60 + ":" +
((totalSecondsLeft % 60 >= 10) ? totalSecondsLeft % 60 : "0" + totalSecondsLeft % 60);
                if (totalSecondsLeft <= 0)
                {
                    submitBTN_Click(null, null);
                }

            };
            answerTime.Start();
        }

        private void initializeServerListener()
        {
            serverListener.WorkerSupportsCancellation = true;
            serverListener.WorkerReportsProgress = true;
            serverListener.DoWork += listenToServer;
            serverListener.ProgressChanged += handleServerMessages;
        }

        private void initializeComponents(GetQuestionResponse response)
        {
            questionLBL.Content = response.question;
            choiceTopLeftBTN.Content = response.possibleAnswers[0];
            choiceTopRightBTN.Content = response.possibleAnswers[1];
            choiceBottomLeftBTN.Content = response.possibleAnswers[2];
            choiceBottomRightBTN.Content = response.possibleAnswers[3];

            //initiating buttins
            this.buttons = new Button[5];
            this.buttons[0] = choiceTopLeftBTN;
            this.buttons[1] = choiceTopRightBTN;
            this.buttons[2] = choiceBottomLeftBTN;
            this.buttons[3] = choiceBottomRightBTN;
            this.buttons[4] = new Button { Content = "wrong answer for sure" };
        }

        public QuestionPage()
        {
            InitializeComponent();
            initializeTimer();
            initializeServerListener();

            Communicator.Send(Communicator.RequestType.GetQuestionRequest, "");
            GetQuestionResponse response = JsonConvert.DeserializeObject<GetQuestionResponse>(Communicator.Receive());
            initializeComponents(response);
        }
        private void listenToServer(object sender, DoWorkEventArgs e)
        {
            while (true)
            {
                if(serverListener.CancellationPending)
                {
                    e.Cancel = true;
                    break;
                }

                if (!Communicator.IsDataAvailable())
                    continue;

                MessageTypeResponse response = JsonConvert.DeserializeObject<MessageTypeResponse>(Communicator.Receive());
                CorrectAnswerResponse correctAnswerResponse = JsonConvert.DeserializeObject<CorrectAnswerResponse>(response.message);
                System.Threading.Thread.Sleep(25); //waiting to maybe receive another response

                if (response.type == MessageTypeResponse.Type.CorrectAnswerResponse)
                {
                    serverListener.ReportProgress((int)MessageTypeResponse.Type.CorrectAnswerResponse, correctAnswerResponse);
                    close(); return;
                }

                else if (response.type == MessageTypeResponse.Type.GetGameResultsResponse)
                {
                    serverListener.ReportProgress(3, correctAnswerResponse);

                    GetGameResultsResponse gameResultsResponse = JsonConvert.DeserializeObject<GetGameResultsResponse>(Communicator.Receive());
                    serverListener.ReportProgress((int)MessageTypeResponse.Type.GetGameResultsResponse, gameResultsResponse);

                    close(); return;
                }
            }
        }

        private void close()
        {
            answerTime.Stop();
            serverListener.CancelAsync();
        }

        private void handleServerMessages(object sender, ProgressChangedEventArgs e)
        {
            switch ((MessageTypeResponse.Type)e.ProgressPercentage)
            {
                case MessageTypeResponse.Type.CorrectAnswerResponse:
                    markCorrectAnswer(((CorrectAnswerResponse)e.UserState).correctAnswer);

                    var timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(2.5) };
                    timer.Start();
                    timer.Tick += (sender, args) =>
                    {
                        timer.Stop();
                        ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage();
                    };
                    break;

                case MessageTypeResponse.Type.GetGameResultsResponse:
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new LoginPage();
                    break;

                case (MessageTypeResponse.Type)3:
                    markCorrectAnswer(((CorrectAnswerResponse)e.UserState).correctAnswer);
                    break;
            }
        }

        private void markCorrectAnswer(String correctAnswer)
        {
            //user didn't choose - all red
            if (this.selectedButtonIndex == 4)
            {
                foreach (ref Button button in this.buttons.AsSpan())
                {
                    button.Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                }
            }
            //user choose right - choice green
            else if (correctAnswer == this.buttons[this.selectedButtonIndex].Content.ToString())
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
            }

            //use choose wrong - choice red, right answer green
            else
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                foreach (ref Button button in this.buttons.AsSpan())
                {
                    if (button.Content.ToString() == correctAnswer)
                    {
                       button.Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
                    }
                }
            }
        }

        private void select(int buttonIndex)
        {
            for (int i = 0; i < this.buttons.Length; i++)
            {
                if (i == buttonIndex) continue;
                this.buttons[i].Background = new BrushConverter().ConvertFrom("#98c9f0") as SolidColorBrush;
            }

            this.buttons[buttonIndex].Background = new BrushConverter().ConvertFrom("#FEE253") as SolidColorBrush;
            this.selectedButtonIndex = buttonIndex;
        }

        private void choiceTopLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(0);
        }

        private void choiceTopRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(1);
        }

        private void choiceBottomLeftBTN_Click(object sender, RoutedEventArgs e)
        {
            select(2);
        }

        private void choiceBottomRightBTN_Click(object sender, RoutedEventArgs e)
        {
            select(3);
        }

        private void submitBTN_Click(object? sender, RoutedEventArgs? e)
        {
            close();
            String selectedAnswer = this.buttons[this.selectedButtonIndex].Content.ToString();

            SubmitAnswerRequest submitRequest;
            submitRequest.answer = selectedAnswer;

            String jsonRepr = JsonConvert.SerializeObject(submitRequest);
            Communicator.Send(Communicator.RequestType.SubmitAnswerRequest, jsonRepr);

            SubmitAnswerResponse submitResponse = JsonConvert.DeserializeObject<SubmitAnswerResponse>(Communicator.Receive());
            serverListener.RunWorkerAsync();
        }
    }
}
