namespace NancySelfHosting
{
    using Nancy;
    using System;
    using System.Diagnostics;

    public class Module : NancyModule
    {
        public Module()
        {
            Get["/"] = parameters => { return answer(parameters); };
        }

        private String answer(dynamic parameters)
        {
            String query = "";
            foreach (var name in Request.Query)
                query += name + ": " + Request.Query[name] + " ";

            Debug.WriteLine(query);

            //add "drop" to response when you need to drop a figure
            return "left=0, right=0, rotate=0";
        }
    }
}
