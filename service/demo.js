import { testAdd } from 'libtest.so'
import Point from './object.js'
testAdd(function (k,v){
    let p=new Point(2,3);
    console.log("k:"+k);
    console.log("v:"+v);
    console.log(p.getAll());
})
console.log("a+b="+(2+3));
console.log(new Date());
