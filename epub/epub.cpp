#include "epub.hpp"


namespace epub
{

    //
    //  /TODO:
    //  http://stackoverflow.com/questions/303371/whats-the-easiest-way-to-generate-xml-in-c
    //

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
    safe(safe),no_cleanup(no_cleanup),vanilla_out(true)
{
    this->m = m;

    std::string stem = boost::filesystem::path(m.get_file_name()).stem().string();
    path_out = boost::filesystem::current_path() / (stem + ".epub");
    path_tmp = boost::filesystem::path("/tmp/mobi/" + stem);
}

void mobi2epub::gen_content_opf(std::stringstream &itemids, std::stringstream &itemrefs) const
{
    std::ofstream outfile(( path_tmp / "/OEBPS/content.opf").c_str());
    outfile << boost::format(content_opf) % this->m.get_title() %itemids.str()\

                                          % itemrefs.str();
    outfile.close();
}


void mobi2epub::directory_structure() const
{

    if(!safe)
    {

        if(boost::filesystem::exists(path_tmp))
        {
            std::cout << boost::filesystem::absolute(path_tmp) << " directory seems to already exist." << std::endl;

            this->cleanup();
        }
        else
        {
            this->safe = true;
        }
    }
    boost::filesystem::create_directories(path_tmp);
    for (auto &x: {"OEBPS","OEBPS/text", "META-INF"})
    {
        boost::filesystem::create_directory(path_tmp / x);
    }


    std::ofstream outfile((path_tmp / "META-INF/container.xml").c_str());
    if(!outfile.good()) { throw file_write_exception(); }
    outfile << container_xml;
    outfile.close();

    outfile.open((path_tmp / "mimetype").c_str());
    if(!outfile.good()) { throw file_write_exception(); }
    outfile << mimetype;
    outfile.close();

}

void mobi2epub::set_out(std::string &s)
{

    boost::filesystem::path path(path_out.parent_path()); 
    boost::filesystem::path filepath(s);
    if(filepath.is_absolute())
    {
        path = filepath;
        filepath = ".";
    }

    if(boost::equals(filepath.filename().string(), ".") 
            or boost::filesystem::is_directory(filepath)) //because has_filename is 
    {                                                     //GOD DAMN BROKEN
        std::string stem = boost::filesystem::path(m.get_file_name()).stem().string();
        path /= filepath / (stem + ".epub");
    }
    else
    {
        path /= s;
    }

    this->vanilla_out = false;
    this->path_out = boost::filesystem::absolute(path);
}

void mobi2epub::save_to_directory(std::string s)
{
    this->set_out(s);
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
        std::string path = (path_tmp / "/OEBPS/text/" / name).string();
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
    if(not safe and boost::filesystem::exists(path_tmp))
    {
        char c;

        std::cout << "Shall we delete " << path_tmp  << " (Y/n): ";
        std::cin >> c;

        if(c != 'Y')
        {
            std::cout << "Continue anyway?: " << path_tmp  << " (Y/n): ";
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
    boost::filesystem::remove_all(path_tmp);
    this->safe = true;
}
void mobi2epub::directory_to_epub(std::string s)
{
    this->set_out(s);
}


void mobi2epub::win_zip() const
{
        throw terrible_operating_system_exception();//FIXME(not the os.)
}

void mobi2epub::lin_zip() const
{
        std::string current_dir = boost::filesystem::current_path().string(); //maybe i do need it?

        chdir(path_tmp.string().c_str());

        std::cout << "saving to " << path_out << std::endl;

        if(system(("zip " + (path_out.string()) + " -qr *").c_str())!=0)
            throw zip_exit_status_exception();

        chdir(current_dir.c_str());

}


void mobi2epub::directory_to_epub() const 
{



    #ifdef _WIN32
    this->win_zip();
    #else
    this->lin_zip();
    #endif
    this->cleanup();
}
}
