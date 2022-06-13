
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
        int timeToAnswer;
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
            serverListener.ProgressChanged += markCorrectAnswer;
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

        public QuestionPage(int time)
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
                String recv = Communicator.Receive();
                CorrectAnswerResponse updateResponse = JsonConvert.DeserializeObject<CorrectAnswerResponse>(recv);

                if (Communicator.IsDataAvailable())
                {
                    GetGameResultsResponse gameResultsResponse = JsonConvert.DeserializeObject<GetGameResultsResponse>(recv);
                    Tuple<CorrectAnswerResponse, GetGameResultsResponse> t = new Tuple<CorrectAnswerResponse, GetGameResultsResponse>(updateResponse, gameResultsResponse);
                    serverListener.ReportProgress(1, t);
                }
                else
                {
                    serverListener.ReportProgress(0, updateResponse);
                }
                
            }
        }

        private void markCorrectAnswer(object sender, ProgressChangedEventArgs e)
        {
            switch (e.ProgressPercentage)
            {
                case 0:
                    mark(((CorrectAnswerResponse)e.UserState).correctAnswer);

                    answerTime.Stop();
                    serverListener.CancelAsync();
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new QuestionPage(timeToAnswer);
                    break;

                case 1:
                    mark(((CorrectAnswerResponse)e.UserState).correctAnswer);

                    answerTime.Stop();
                    serverListener.CancelAsync();
                    ((MainWindow)Application.Current.MainWindow).frame.Content = new LoginPage();
                    break;
            }
        }

        private void mark(String correctAnswer)
        {
            if (correctAnswer == this.buttons[this.selectedButtonIndex].Content.ToString())
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
            }
            else
            {
                this.buttons[this.selectedButtonIndex].Background = new BrushConverter().ConvertFrom("#eb8496") as SolidColorBrush;
                foreach (ref Button button in this.buttons.AsSpan())
                {
                    if (button.Content.ToString() == correctAnswer)
                    {
                        button.Background = new BrushConverter().ConvertFrom("#a2e2bb") as SolidColorBrush;
                        break;
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
            answerTime.Stop();
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
