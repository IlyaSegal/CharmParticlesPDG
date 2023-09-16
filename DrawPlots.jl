using Corpuscles
using Unitful
using CairoMakie

# Initialize list of particles and colours of quarks
particles = [Particle(-411), Particle(411), Particle(421), Particle(4122), Particle(4222), Particle(4212), Particle(4112), Particle(4232), Particle(4132), Particle(4332)]
colours = Dict('u'=>"red",'d'=>"blue",'s'=>"magenta",'c'=>"green3",'U'=>"crimson",'D'=>"royalblue1",'S'=>"purple",'C'=>"green")

ħ = 6.582e-22u"MeV*s" # Planck's constant for calculation of a lifetime

# Create pies
pies_fig = Figure(resolution = (2000, 800))
for (i, particle) in enumerate(particles)
    # Set position of pies on the figure
    if (i <= 5) 
       x = 1
       y = i
    else 
       x = 2
       y = i-5
    end
    # Case of mesons
    if (sizeof(particle.quarks) == 2)
    	ax = Axis(pies_fig[x, y], title = string(particle.name, " (", particle.quarks[1], particle.quarks[2], ")"))
	limits!(ax, (-0.35, 0.35), (-0.35, 0.35))
	hidedecorations!(ax)
	hidespines!(ax)
	pie!(
    	    pies_fig[x, y],
    	    [1, 1],
    	    color = [colours[particle.quarks[1]], colours[particle.quarks[2]]],
	    radius = 0.2*sqrt((uconvert(u"ps",(ħ/particle.width.value/u"c^2")))/u"ps")
	   )
    # Case of baryons
    else
    	ax = Axis(pies_fig[x, y], title = string(particle.name, " (", particle.quarks[1], particle.quarks[2], particle.quarks[3], ")"))
	limits!(ax, (-0.35, 0.35), (-0.35, 0.35))
	hidedecorations!(ax)
	hidespines!(ax)
    	pie!(
    	    pies_fig[x, y],
    	    [1, 1, 1],
    	    color = [colours[particle.quarks[1]], colours[particle.quarks[2]], colours[particle.quarks[3]]],
	    radius = 0.2*sqrt((uconvert(u"ps",(ħ/particle.width.value/u"c^2")))/u"ps")
	   )
    end 
end

display(pies_fig)
