import { testAdd } from 'libtest.so'
import { Point } from 'libpoint.so'
import { HttpContext } from  'libhttp-context.so'
import JSPoint from './object.js'
import {initDispatcher,addRoute} from 'libhttp-route.so'


testAdd(function (r,c){
    let p=new JSPoint(2,3);
    console.log("r:"+r);
    console.log("c:"+c);
    console.log(p.getAll());
    let p1=new Point(4,5);
    console.log(p1.x)
    console.log(p1.norm())
})

initDispatcher();

addRoute("home",new Point(4,5));

let httpContext=new HttpContext();

console.log(httpContext.service());

console.log("a+b="+(2+3));
console.log(new Date());
