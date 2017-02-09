#include <Crimild.hpp>
#include <Crimild_Import.hpp>

using namespace crimild;
using namespace crimild::messaging;
using namespace crimild::import;

SharedPointer< Node > convert( std::string inputFile, std::string outputFile )
{
    Clock c;

    c.tick();

    SceneImporter importer;
    auto model = importer.import( FileSystem::getInstance().pathForResource( inputFile ) );
    if ( model == nullptr ) {
        return nullptr;
    }

    c.tick();
    Log::info( "CONVERTER", "Loading raw model: ", c.getDeltaTime(), "s" );

    {
        FileStream os( FileSystem::getInstance().pathForResource( outputFile ), FileStream::OpenMode::WRITE );
        os.addObject( model );
        if ( !os.flush() ) {
            return nullptr;
        }
    }
    c.tick();
    Log::info( "CONVERTER", "Saving stream: ", c.getDeltaTime(), "s" );

    FileStream is( FileSystem::getInstance().pathForResource( outputFile ), FileStream::OpenMode::READ );
    if ( !is.load() ) {
        Log::error( "Load failed" );
        return nullptr;
    }

    c.tick();
    Log::info( "CONVERTER", "Loading stream: ", c.getDeltaTime(), "s" );

    if ( is.getObjectCount() == 0 ) {
        Log::error( "File is empty?" );
        return nullptr;
    }

    return is.getObjectAt< Node >( 0 );   
}

void printUsage( void )
{
	std::cout << "\nUsage: "
			  << "\n\t./crimild-converter input=<INPUT_FILE> [ouput=<OUTPUT_FILE>]"
			  << "\n\n";
}

int main( int argc, char **argv )
{
	Log::setLevel( Log::Level::LOG_LEVEL_INFO );

	auto settings = crimild::alloc< Settings >( argc, argv );

	AssetManager assetManager;

    std::string inputPath = settings->get< std::string >( "input", "" );
    if ( inputPath == "" ) {
    	printUsage();
    	return -1;
    }

    std::string outputPath = settings->get< std::string >( "ouput", "scene.crimild" );

    auto convertedModel = convert( inputPath, outputPath );
    if ( convertedModel == nullptr ) {
    	Log::error( "CONVERTER", "Failed to convert model" );
    	return -1;
    }

    Log::info( "CONVERTER", "Success" );

    return 0;
}

