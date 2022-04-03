class GradientDescender :
    def __init__(self, func:dict) -> None :
        self.func = func
        self.differential = self.get_differential(func)

    def __str__(self) :
        resulf = ""
        
    def get_differential(func:dict) :
        differential = {}
        for k, v in func.items() :
            differential[k - 1] = v * k

    def funcToStr(func:dict) :
        result = ""
        for k, v in func.items() :
            result += str(v)
            if k :
                result += str(k)
            result += " + "