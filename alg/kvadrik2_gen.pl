#!/usr/bin/perl

$prog = $0 ;
$prog =~ s/\.pl// ;

@surf = (
  {'name' => 'pmip', rusname => 'пара мнимых пересекающихся прямых', 'eqn' => 'x^2+y^2=0',
    'r' => 2, 'rp' => 2, 'rm' => 0, 'type' => 2, 'a' => 0
  },
  {'name' => 'me', rusname => 'мнимый эллипс', 'eqn' => 'x^2+y^2+1=0',
    'r' => 2, 'rp' => 2, 'rm' => 0, 'type' => 2, 'a' => 1
  },
  {'name' => 'e', rusname => 'эллипс', 'eqn' => 'x^2+y^2-1=0',
    'r' => 2, 'rp' => 2, 'rm' => 0, 'type' => 2, 'a' => -1
  },
  {'name' => 'pip', rusname => 'пара пересекающихся прямых', 'eqn' => 'x^2-y^2=0',
    'r' =>2, 'rp' => 1, 'rm' => 1, 'type' => 2, 'a' => 0
  },
  {'name' => 'g', rusname => 'гиперболa', 'eqn' => 'x^2-y^2+1=0',
    'r' => 2, 'rp' => 1, 'rm' => 1, 'type' => 2, 'a' => 1
  },
  {'name' => 'p', rusname => 'парабола', 'eqn' => 'x^2+y=0',
    'r' => 1, 'rp' => 1, 'rm' => 0, 'type' => 1
  },
  {'name' => 'psp', rusname => 'пара совпадающих прямых', 'eqn' => 'x^2=0',
    'r' => 1, 'rp' => 1, 'rm' => 0, 'type' => 2, 'a' => 0
  },
  {'name' => 'pmpp', rusname => 'пара мнимых параллельных прямых', 'eqn' => 'x^2+1=0',
    'r' => 1, 'rp' => 1, 'rm' => 0, 'type' => 2, 'a' => 1
  },
  {'name' => 'ppp', rusname => 'пара параллельных прямых', 'eqn' => 'x^2-1=0',
    'r' => 1, 'rp' => 1, 'rm' => 0, 'type' => 2, 'a' => -1
  }
  
) ;
$num = int(rand(9)) ;
%s = %{$surf[$num]} ;
print STDERR "Ответ:\n\nКривая: $s{'rusname'}\n\n" ;
print STDERR "Канонический вид: \$ $s{'eqn'} \$\n\n" ;
print STDERR "ранг: $s{'r'}, сигнатура: ($s{'rp'}, $s{'rm'})\n\n" ;

$string  = "$s{'r'} $s{'rm'} $s{'type'} " ;
$string .= "$s{'a'}" if $s{'type'} == 2 ;
print `echo "$string" | $prog` ;

for $key (keys %s) {
    print "\n\%$key=\n\%$s{$key}\n"
}

