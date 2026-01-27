// Without interface segregation 
typedef int Docs;
struct BAD_IMachine{
    virtual void print(Docs) = 0;
    virtual void scan(Docs) = 0;
    virtual void fax(Docs) = 0;
};

// if i want a scanner
struct BAD_Scanner: BAD_IMachine{
    void print(Docs d) {return;}
    void scan(Docs d) { /* logic for scan only */}
    void fax(Docs d) {return;}
};

// Segregating interfaces
struct IPrinter{ virtual void print(Docs) = 0;};
struct IScanner{ virtual void scan(Docs) = 0;};
struct IFaxxer{ virtual void fax(Docs) = 0;};
struct IMachine: IPrinter, IScanner, IFaxxer{};

struct Scanner: IScanner{/*Concrete implementation*/};
struct Machine: IMachine{
    IScanner& scanner;
    IPrinter& printer;
    Machine(IPrinter& p, IScanner& s): scanner(s), printer{p}{}
    void print(Docs d) override { printer.print(d); }
    void scan(Docs d) override { scanner.scan(d); }

};
int main(){
    return 0;
}