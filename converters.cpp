#include <converters.h>


bool ConvertToFormat_RGB888(gdcm::Image const & gimage, char *buffer, QImage* &imageQt){
    const unsigned int* dimension = gimage.GetDimensions();

    unsigned int dimX = dimension[0];
    unsigned int dimY = dimension[1];

    gimage.GetBuffer(buffer);

    // Let's start with the easy case:
    if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::RGB )
      {
      if( gimage.GetPixelFormat() != gdcm::PixelFormat::UINT8 )
        {
        return false;
        }
      unsigned char *ubuffer = reinterpret_cast<unsigned char*>(buffer);
      // QImage::Format_RGB888  13  The image is stored using a 24-bit RGB format (8-8-8).
      imageQt = new QImage(reinterpret_cast<unsigned char*>(ubuffer), static_cast<int>(dimX), static_cast<int>(dimY),
                           static_cast<int>(3*dimX), QImage::Format_RGB888);
      }
    else if( gimage.GetPhotometricInterpretation() == gdcm::PhotometricInterpretation::MONOCHROME2 )
      {
      if( gimage.GetPixelFormat() == gdcm::PixelFormat::UINT8 )
        {
        // We need to copy each individual 8bits into R / G and B:
        unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
        unsigned char *pubuffer = ubuffer;
        for(unsigned int i = 0; i < dimX*dimY; i++)
          {
          *pubuffer++ = *buffer;
          *pubuffer++ = *buffer;
          *pubuffer++ = *buffer++;
          }

        imageQt = new QImage(ubuffer, static_cast<int>(dimX), static_cast<int>(dimY), QImage::Format_RGB888);
        }
      else if( gimage.GetPixelFormat() == gdcm::PixelFormat::INT16 )
        {
        // We need to copy each individual 16bits into R / G and B (truncate value)
        short *buffer16 = reinterpret_cast<short*>(buffer);
        unsigned char *ubuffer = new unsigned char[dimX*dimY*3];
        unsigned char *pubuffer = ubuffer;
        for(unsigned int i = 0; i < dimX*dimY; i++)
          {
          // Scalar Range of gdcmData/012345.002.050.dcm is [0,192], we could simply do:
          // *pubuffer++ = *buffer16;
          // *pubuffer++ = *buffer16;
          // *pubuffer++ = *buffer16;
          // instead do it right:
          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
          *pubuffer++ = static_cast<unsigned char>(std::min(255, (32768 + *buffer16) / 255));
          buffer16++;
          }

        imageQt = new QImage(ubuffer, static_cast<int>(dimX), static_cast<int>(dimY), QImage::Format_RGB888);
        }
      else
        {
        std::cerr << "Pixel Format is: " << gimage.GetPixelFormat() << std::endl;
        return false;
        }
      }
    else
      {
      std::cerr << "Unhandled PhotometricInterpretation: " << gimage.GetPhotometricInterpretation() << std::endl;
      return false;
      }

    return true;

}

int PrintCSA(const std::string filename){
    gdcm::Reader reader;
    reader.SetFileName(filename.c_str());
    if(!reader.Read()){
        std::cerr<<"Failed to load image in gdcm reader";
        return 1;
    }
    gdcm::CSAHeader csa;
    const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

    const gdcm::PrivateTag &imageRef = csa.GetCSAImageHeaderInfoTag();
    const gdcm::PrivateTag &seriesRef = csa.GetCSASeriesHeaderInfoTag();
    const gdcm::PrivateTag &dataRef = csa.GetCSADataInfo();

    bool found = false;
    int ret = 0;
    if(ds.FindDataElement(imageRef)){
        csa.LoadFromDataElement(ds.GetDataElement(imageRef));
        csa.Print(std::cout);
        found = true;
        if(csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT){
            std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
            ret = 1;
        }
        else if(csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT){
            gdcm::Printer p;
            gdcm::File f;
            f.SetDataSet(csa.GetDataSet());
            p.SetFile( f );
            p.Print(std::cout);
        }

    }
    if ( ds.FindDataElement(seriesRef)){
        csa.LoadFromDataElement( ds.GetDataElement( seriesRef ) );
           csa.Print( std::cout );
           found = true;
           if( csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT )
             {
             std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
             ret = 1;
             }
           else if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
             {
             gdcm::Printer p;
             gdcm::File f;
             f.SetDataSet( csa.GetDataSet() );
             p.SetFile( f );
             p.Print( std::cout );
             }
    }
    if (ds.FindDataElement(dataRef)){
        csa.LoadFromDataElement( ds.GetDataElement( dataRef ) );
            csa.Print( std::cout );
            found = true;
            if( csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT )
              {
              std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
              ret = 1;
              }
            else if( csa.GetFormat() == gdcm::CSAHeader::INTERFILE )
              {
              const char *interfile = csa.GetInterfile();
              if( interfile ) std::cout << interfile << std::endl;
              }
            else if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
              {
              gdcm::Printer p;
              gdcm::File f;
              f.SetDataSet( csa.GetDataSet() );
              p.SetFile( f );
              p.Print( std::cout );
              }
    }
    if( !found )
      {
      std::cout << "no csa tag found" << std::endl;
      ret = 1;
      }
    return ret;
}


bool CEcho(){
    return gdcm::CompositeNetworkFunctions::CEcho("localhost",6666, "KAF46-TITLE"
                                                                    "");
}
