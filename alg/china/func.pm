package func;
  require Exporter;        
  @ISA	= qw(Exporter);    
  @EXPORT = qw(query_decode hash_var no_input wrong_input true_input strip_all strip gen_rand_poly str2pdl str2poly list2poly); 

sub query_decode  {
  my $str = shift ;
  @args = split /\=|\&/, $str ;
  foreach $val (@args) {
	$val =~ y/\+/ / ;
	$val =~ s/%([A-Fa-f\d]{2})/chr(hex($1))/eg;
  }
  return @args ;
}

sub hash_var {
  my $str = shift ;
  $str = $' if $str =~ /%/ ;
  $str =~ s/%//g ;
  $str =~ y/\r\t / /s ;
  $str =~ s/(\n){2,}/\n\n/g ;
  $str =~ s/\n\n/new_item/mg ;
  $str =~ s/^\s+//mg ;
  return split /=\n|new_item/, $str ;
}

sub no_input {
  my $val = shift ;
  print "<tr><td style='text-align:right'>$val:</td>\n".
		"<td style='text-align:left; color:gray'>не введено</td></tr>\n" ;
}

sub wrong_input {
  my $val = shift ;
  print "<tr><td style='text-align:right'>$val:</td>\n".
		"<td style='text-align:left; color:red'>не верно</td></tr>\n" ;
}

sub true_input {
  my $val = shift ;
  print "<tr><td style='text-align:right'>$val:</td>\n".
		"<td style='text-align:left; color:green'>верно</td></tr>\n" ;
}

sub strip_all {
  my $str = shift ;
  $str =~ s/[\n\t\r,; ]//g ;
  return $str
}

sub strip {
  my $str = shift ;
  $str =~ y/\n\t\r,; /       /s ;
  return $str
}

sub str2pdl {
  my $str = $_[0] ;
  $str =~ y/\r \n/\n,\n/s ;
  $str =~ s/(^|\n),/$1/g ;
  $str =~ s/\n(.)/\],\[$1/g ;
  chomp($str) ;
  return pdl eval "[[$str]]" ;
}

sub gen_rand_poly {
  my ($deg, $max, $uni) = @_ ;
  my @coef ;
  for $i (0 .. $deg) {
    push @coef, Math::BigInt->new(int(rand(2*$max+1))-$max) ; 
  }
  $coef[$deg] = Math::BigInt->new(1) if $uni == 1 ;
  $coef[$deg] = Math::BigInt->new(int(rand(2*$max+1))-$max)
    while $coef[$deg] == Math::BigInt->new(0) ;
  $bgcd = Math::BigInt::bgcd(@coef) ;
  if ($deg != 0 ) {
    for $i (@coef) { $i = Math::BigRat->new($i/$bgcd) } ;
  };
  $ret = Math::Polynomial->new(@coef) ;
  $ret = -$ret if $ret->coeff($ret->degree) < 0 && $deg != 0 ;
  $ret->string_config({fold_sign => 1, prefix => '', suffix => ''}) ;
  return $ret ;
}

sub str2poly {
  my @qcf, my $ret, my @cf = ( shift =~ /([+-\/0-9]+)/g ) ;
  for $num (@cf) { push @qcf, Math::BigRat->new($num) ;  } ;
  my $ret = Math::Polynomial->new(@qcf) ;
  $ret->string_config({fold_sign => 1, prefix => '', suffix => ''}) ;
  return $ret ;
}


sub list2poly {
  my @qcf ;
  for $num (@_) { push @qcf, Math::BigRat->new($num) ;  } ;
  my $ret = Math::Polynomial->new(@qcf) ;
  $ret->string_config({fold_sign => 1, prefix => '', suffix => ''}) ;
  return $ret ;
}
