#!/usr/bin/perl

use Archive::Tar;
use IO::Zlib;
use File::Copy;

my $USAGE = "  Usage: $0 FILENAME\n";

my $tar_file = $ARGV[0] 
  or die $USAGE;

my $tar = Archive::Tar->new($tar_file);

my @files_to_remove;
foreach my $file ( sort $tar->list_files( ['name'] ) )
{
  if ($file =~ '/\._' or $file =~ '.DS_Store')
  {
    push @files_to_remove, $file;
  }
}

unless ( scalar(@files_to_remove) )
{
  exit;
}


$tar->remove(@files_to_remove);

$tar->write($tar_file, 1);
