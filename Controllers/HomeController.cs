using Microsoft.AspNetCore.Mvc;

namespace ZieOnsServer.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
