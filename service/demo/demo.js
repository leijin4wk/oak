import { testAdd } from 'libtest.so'

let r=testAdd(1, 0.5,function (v){
    console.log("param:"+v);
})
console.log("r="+r)
let a=2;
let b=3;
console.log("a+b="+(a+b));
console.log(new Date());
