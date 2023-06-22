namespace Frontend.Responses
{
    public struct RoomData
    {
        public int id;
        public string name;
        public int maxPlayers;
        public int numOfQuestionsInGame;
        public int timePerQuestion;
        public bool isActive;
    }
}