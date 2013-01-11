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

mobi2epub::mobi2epub(const mobi::mobireader &m, bool safe, bool no_cleanup):\
    safe(safe),no_cleanup(no_cleanup),vanilla_base(true)
{
    this->m = m;
    base = this->m.get_file_name().substr(0, this->m.get_file_name().find_last_of('.'));
    base = boost::filesystem::absolute(base);
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
    for (auto x: {"OEBPS","OEBPS/text", "META-INF"})
    {
        boost::filesystem::create_directory(base / x);
    }


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


    std::stringstream itemids;
    std::stringstream itemrefs;

    html::tidyhtml tidyh;

    unsigned i = 0;
    for(std::string &x: v)
    {
        std::string name = "chapter" + std::to_string(++i) + ".html";

        boost::replace_all(x, "filepos=", "id=");

        std::string path = (base / "/OEBPS/text/" / name).string();
        tidyh.parse(x, path);

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

        if(c == 'Y')
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
{   
    std::string filename_base = base.stem().string() + ".epub";
    std::string current_dir = boost::filesystem::current_path().string();
    std::string start_path = boost::filesystem::absolute(base).string();


    chdir(boost::filesystem::absolute(base).c_str());

    #ifdef _WIN32
        throw terrible_operating_system_exception();//FIXME(not the os.)
    #else

        boost::filesystem::path p(current_dir);
        p/=filename_base;

        std::cout << "saving to " << p.string() << std::endl;

        if(system(("zip " + p.string() + " -qr *").c_str())!=0)
            throw zip_exit_status_exception();

        chdir(current_dir.c_str());

    #endif
        this->cleanup();
}
}
