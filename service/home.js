import { HttpContext } from  'libhttp-context.so'

export default class Home extends HttpContext{
    constructor() {
        super();
    }
    service() {
        return "son service";
    }
}