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
		
		const int DO_NOT_ROTATE = 0, ROTATE_90_CLOCKWISE = 1, ROTATE_180_CLOCKWISE = 2, ROTATE_90_COUNTERCLOCKWISE = 3;

        private String answer(dynamic parameters)
        {
            String query = "";
            foreach (var name in Request.Query)
                query += name + ": " + Request.Query[name] + " ";

            Debug.WriteLine(query);

            // add "drop" to response when you need to drop a figure
			// for details please check http://codenjoy.com/portal/?p=170#commands			
            return "left=0, right=0, rotate=0";
        }
    }
}
