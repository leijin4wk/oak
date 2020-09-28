import { testAdd } from 'libtest.so'
import { Point } from 'libpoint.so'
import JSPoint from './object.js'

testAdd(function (r,c){
    let p=new JSPoint(2,3);
    console.log("r:"+r);
    console.log("c:"+c);
    console.log(p.getAll());
    let p1=new Point(4,5);
    console.log(p1.x)
    console.log(p1.norm())
})

console.log("a+b="+(2+3));
console.log(new Date());
