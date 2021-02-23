using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp
{
    class Parent
    {
        public int param = 1;
        public void Print()
        {
            Console.WriteLine("I'm Parent");
        }

        public virtual void PrintEx()
        {
            Console.WriteLine("I'm Parent PrintEx");
        }
    }

    class Chlid : Parent
    { 
        new public int param = 2;  //显示覆盖基类参数
        public new void Print()
        {
            Console.WriteLine("I'm Chlid");
        }

        public override void PrintEx()
        {
            Console.WriteLine("I'm Chlid PrintEx");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Parent parent = new Parent();
            Parent parent2 = new Chlid();
            Chlid child = new Chlid();

            //1,1,2
            Console.WriteLine("parent.param:"+ parent.param);  
            Console.WriteLine("parent2.param:" + parent2.param);
            Console.WriteLine("child.param:" + child.param);


            //I'm Parent
            //I'm Parent  new代表属于当前类的，不重写基类的变量或接口
            //I'm Chlid
            //------------------------
            //I'm Parent PrintEx
            //I'm Chlid PrintEx   override 直接重写接口
            //I'm Chlid PrintEx

            parent.Print();
            parent2.Print();
            child.Print();

            Console.WriteLine("------------------------");

            parent.PrintEx();
            parent2.PrintEx();
            child.PrintEx();

            Console.ReadLine();
        }
    }
}
