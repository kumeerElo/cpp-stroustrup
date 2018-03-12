#!/usr/bin/env perl

use strict;
use warnings;

sub get_hour()
{
	my ($hour) = @_;
	my @vec = split(/:/, $hour);
	my $size = scalar @vec;
	if ($size != 3){
		print "wrong parsing in get_hour()\n";
		exit;
	}
	return $vec[0]; #hour part of the time string
}

sub parse_local_time()
{
	my $tm = localtime;
	my @vec = split(/\s+/, $tm);
	my $size = scalar @vec;
	if ($size != 5){
		print "wrong parsing in parse_local_time()\n";
		exit;
	}
	my $month = $vec[1];
	my $date  = $vec[2];
	my $hour	= &get_hour($vec[3]);
	return ($month, $date, $hour);	
}

#main
my ($month, $date, $hour)= parse_local_time();
my $dirName = join('_', $hour, $date, $month);

my $targetDir= join('/', "/home/mks/bakup",$dirName);

if (-e $targetDir){
	print "$targetDir exists already - removing the dir\n";
	system ("rm -rf $targetDir");
}

mkdir $targetDir or die "couldn't create dir: $targetDir\n";

my $sourceDir = "/home/mks/cpp_book";

print ("copying files from $sourceDir to $targetDir\n");
system("cp -rf $sourceDir $targetDir");
print "DONE!\n";
