#include "epub.hpp"


namespace epub
{

std::string container_xml =
"<?xml version=\"1.0\"?>\n\
<container version=\"1.0\" xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\">\n\
   <rootfiles>\n\
      <rootfile full-path=\"OEBPS/content.opf\" media-type=\"application/oebps-package+xml\"/>\n\
      \n\
   </rootfiles>\n\
</container>";
std::string mimetype = "application/epub+zip";

std::string itemid  = "    <item id=\"%1%\" href=\"text/%1%\" media-type=\"application/xhtml+xml\" />\n";
std::string itemref = "    <itemref idref=\"%1%\" />\n";

//%1% - <item id="foo" href="text/foo.html" media-type="text/html(application/xhtml+xml?)" />"
//%2% - <itemref idref=id />

std::string content_opf = "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\
<package xmlns=\"http://www.idpf.org/2007/opf\" unique-identifier=\"BookId\" version=\"2.0\">\n\
    <metadata xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:opf=\"http://www.idpf.org/2007/opf\">\n\
        <dc:title>%1%</dc:title> \n\
    </metadata>\n\
    <manifest>\n\n\
\
%2%\n\
\
    </manifest>\n\
    <spine toc=\"ncx\">\n\n\
\
%3%\n\
\
    </spine>\n\
</package>\n\
";

mobi2epub::mobi2epub(const mobi::mobireader &m, bool safe, bool no_cleanup):safe(safe),no_cleanup(no_cleanup),vanilla_base(true)
{
    this->m = m;
    base = "~tmp_" + this->m.get_file_name().substr(0, this->m.get_file_name().find_last_of('.'));
}

void mobi2epub::gen_content_opf(std::stringstream &itemids, std::stringstream &itemrefs) const
{
    std::ofstream outfile(( base / "/OEBPS/content.opf").c_str());
    outfile << boost::format(content_opf) % this->m.get_title() %itemids.str()\
                                          % itemrefs.str();
    outfile.close();
}


void mobi2epub::directory_structure() const
{

    if(!safe)
    {

        if(boost::filesystem::exists(base))
        {
            std::cout << boost::filesystem::absolute(base) << " directory seems to already exist." << std::endl;

            this->cleanup();
        }
        else
        {
            this->safe = true;
        }
    }
    boost::filesystem::create_directory(base);
    boost::filesystem::create_directory(base / "OEBPS");
    boost::filesystem::create_directory(base / "OEBPS" / "text");
    boost::filesystem::create_directory(base / "META-INF");

    std::ofstream outfile((base / "META-INF/container.xml").c_str());
    if(!outfile.good()) { throw file_write_exception(); }
    outfile << container_xml;
    outfile.close();

    outfile.open((base / "mimetype").c_str());
    if(!outfile.good()) { throw file_write_exception(); }
    outfile << mimetype;
    outfile.close();

}

void mobi2epub::set_base(std::string &s)
{
    if(boost::iends_with(s,".epub"))
        boost::erase_last(s,".epub");

    this->vanilla_base = false;
    this->base = s;
}

void mobi2epub::save_to_directory(std::string s)
{
    this->set_base(s);
    this->save_to_directory();
}

void mobi2epub::save_to_directory() const
{

    this->directory_structure();

    std::string foo = m.get_html();

    std::vector<std::string> v;
    iter_split(v, foo, boost::algorithm::first_finder("<mbp:pagebreak/>"));

    unsigned i = 0;

    std::stringstream itemids;
    std::stringstream itemrefs;

    TidyDoc tdoc = tidyCreate();

    //16,035 (4,952 direct, 11,083 indirect) bytes in 1 blocks are definitely lost in loss record 48 of 48
    //tidyhtml, stahp.

    tidyOptSetBool( tdoc, TidyXhtmlOut, yes);
    tidyOptSetBool( tdoc, TidyForceOutput, yes);
    tidyOptSetBool( tdoc, TidyShowWarnings, no);
    tidyOptSetBool( tdoc, TidyQuiet, yes);

    tidyOptSetInt( tdoc, TidyShowErrors, 0);
    tidySetCharEncoding(tdoc, "utf8");

    for(std::string &x: v)
    {
        std::string name = "chapter" + std::to_string(++i) + ".html";

        boost::replace_all(x, "filepos=", "id=");

        //here be dragons
        tidySetErrorBuffer(tdoc, NULL);
        tidyParseString(tdoc, x.c_str());
        tidyCleanAndRepair( tdoc );
        tidyRunDiagnostics( tdoc );
        tidySaveFile(tdoc, (base / "/OEBPS/text/" / name).c_str());

        itemids << boost::format(itemid) % name;
        itemrefs <<  boost::format(itemref) % name;
    }

    this->gen_content_opf(itemids,itemrefs);
}

void mobi2epub::cleanup() const
{
    if(this->no_cleanup)
    {
        return;
    }
    if(not safe)
    {
        char c;

        std::cout << "Shall we delete " << base  << " (Y/n): ";
        std::cin >> c;

        if(c != 'Y')
        {
            std::cout << "Continue anyway?: " << base  << " (Y/n): ";
            std::cin >> c; //because who would expect a sane behavior.
            if(c != 'Y'){ throw user_wants_out_exception(); }
            else
            {

                this->safe=true;
                this->no_cleanup=true;
                return;
            }
                
        }
    }
    boost::filesystem::remove_all(base);
    this->safe = true;
}
void mobi2epub::directory_to_epub(std::string s)
{
    this->set_base(s);
}

void mobi2epub::directory_to_epub() const
{   //TODO: make it better, although it seems like the only C++ library
    //that does it and has documentation, depends on Qt.
    //░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
    //░█░░░█▀█░█░░░█▀█░█▀█░█▀█░█▀▀░
    //░█░░░█░█░█░░░█░█░█░█░█▀▀░█▀▀░
    //░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░░░▀▀▀░
    //░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
    std::string filename_base;
    if(this->vanilla_base)
        filename_base = base.string().substr(5);
    else
        filename_base = base.string();
    filename_base = filename_base + ".epub";

    #ifdef _WIN32
        throw terrible_operating_system_exception();//FIXME(not the os.)
    #else
        std::string start_path = boost::filesystem::absolute(base).string();
        chdir(boost::filesystem::absolute(base).c_str()); //FIXME: absolute paths more absolute.
        if(system(("zip ../" + filename_base + " -qr *").c_str())!=0)
            throw zip_exit_status_exception();

        chdir("..");
        if(start_path != boost::filesystem::absolute(base))
            throw path_changed_exception();
    #endif
        this->cleanup();
}
}
