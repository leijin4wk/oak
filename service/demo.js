import { testAdd } from 'libtest.so'
import { Point } from 'libpoint.so'
import JSPoint from './object.js'
import {initDispatcher,addRoute} from 'libhttp-route.so'
import Home from './home.js'



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

addRoute("home",new Home());

let home=new Home();
console.log(home.service())

console.log("a+b="+(2+3));
console.log(new Date());

let a, s;
s = '{"x":1,"y":true,"z":null,"a":[1,2,3],"s":"str"}';
a = JSON.parse(s);
console.log(a.x);
console.log(a.y);
console.log(a.z);
console.log(a.a);
console.log(a.s);
let obj={
    a:1,
    b:2
}
let str=JSON.stringify(obj);
console.log(str)

