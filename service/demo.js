import { testAdd } from 'libtest.so'
import Point from './object.js'
testAdd(function (r,c){
    let p=new Point(2,3);
    console.log("r:"+r);
    console.log("c:"+c);
    console.log(p.getAll());
})
console.log("a+b="+(2+3));
console.log(new Date());
